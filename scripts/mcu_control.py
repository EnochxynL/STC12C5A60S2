#!/usr/bin/env python3
"""STC12C5A60S2 实验控制脚本"""

import serial
import sys
import time
import argparse

# 命令字节
CMD = {
    "speed": 0xDE,     # 速度实验
    "temp": 0xDF,      # 温度实验
    "open": 0xEA,      # 开环
    "close": 0xEB,     # 闭环
    "start": 0xEE,     # 启动
    "stop": 0xED,      # 停止
    "reset": 0xEC,     # 软件复位
}


def connect(port, baud=57600):
    ser = serial.Serial(port, baud, timeout=0.5)
    print(f"已连接 {port} @ {baud}")
    return ser


def send_cmd(ser, byte):
    ser.write(bytes([byte]))
    print(f"发送: 0x{byte:02X} ({chr(byte) if 0x20 <= byte < 0x7F else '?'})")


def send_value(ser, val):
    """发送3位ASCII数字，如 val=50 -> '050'"""
    data = f"{val:03d}".encode()
    ser.write(data)
    print(f"发送设定值: {val}")


def recv_data(ser):
    """解析MCU返回的数据: 0xFF Lbyte Hbyte"""
    buf = ser.read(32)
    if not buf:
        return None

    for i in range(len(buf) - 2):
        if buf[i] == 0xFF:
            val = buf[i + 1] + (buf[i + 2] << 8)
            return val
    return None


def main():
    parser = argparse.ArgumentParser(description="MCU实验控制")
    parser.add_argument("-p", "--port", default="/dev/ttyUSB0", help="串口号")
    parser.add_argument("-b", "--baud", type=int, default=57600, help="波特率")
    parser.add_argument("--mode", choices=["speed", "temp"], help="实验模式")
    parser.add_argument("--loop", choices=["open", "close"], help="开/闭环")
    parser.add_argument("--set", type=int, help="设定值 (0-170)")
    args = parser.parse_args()

    ser = connect(args.port, args.baud)
    print("=" * 50)
    print("命令: speed|temp|open|close|start|stop|reset|set=N|recv|quit")
    print("示例: speed -> open -> set=50 -> start")
    print(f"模式: {args.mode or '无'}, 开/闭环: {args.loop or '无'}, 设定值: {args.set or '无'}")
    print("=" * 50)

    # 如果有命令行参数，自动发送
    steps = []
    if args.mode:
        steps.append(args.mode)
    if args.loop:
        steps.append(args.loop)
    if args.set is not None:
        steps.append(f"set={args.set}")
    steps.append("start")

    if len(steps) > 1:
        print("自动执行:", " -> ".join(steps))
        for s in steps:
            if s == "start":
                send_cmd(ser, CMD["start"])
            elif s.startswith("set="):
                send_value(ser, int(s.split("=")[1]))
            else:
                send_cmd(ser, CMD[s])
            time.sleep(0.1)

        print("\n等待MCU返回数据...")
        while True:
            try:
                val = recv_data(ser)
                if val is not None:
                    print(f"收到: {val}")
            except KeyboardInterrupt:
                break
        return

    # 交互模式
    while True:
        try:
            cmd = input("> ").strip().lower()
            if not cmd:
                continue
            if cmd in ("quit", "exit", "q"):
                break
            if cmd in CMD:
                send_cmd(ser, CMD[cmd])
            elif cmd.startswith("set="):
                send_value(ser, int(cmd.split("=")[1]))
            elif cmd == "recv":
                val = recv_data(ser)
                if val is not None:
                    print(f"收到: {val}")
                else:
                    print("无数据")
            else:
                print(f"未知命令: {cmd}")
        except KeyboardInterrupt:
            break

    ser.close()
    print("已断开")


if __name__ == "__main__":
    main()
