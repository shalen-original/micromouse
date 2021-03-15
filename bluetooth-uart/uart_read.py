import sys, logging
import asyncio

from bleak import BleakClient
from bleak import _logger as logger

# https://learn.adafruit.com/introducing-adafruit-ble-bluetooth-low-energy-friend/uart-service
UART_RX_UUID = "0x0003"
MAC_ADDRESS = "AA:AA:AA:AA:AA:AA"

def on_msg_received(sender, data):
    print("{0}: {1}".format(sender, data))

async def uart_read(address):
    async with BleakClient(address) as client:
        logger.info(f"Connected: {client.is_connected}")

        await client.start_notify(UART_RX_UUID, on_msg_received)

l = logging.getLogger("asyncio")
l.setLevel(logging.DEBUG)
h = logging.StreamHandler(sys.stdout)
h.setLevel(logging.DEBUG)
l.addHandler(h)
logger.addHandler(h)

loop = asyncio.get_event_loop()
loop.run_until_complete(uart_read(MAC_ADDRESS))
loop.run_forever()