import asyncio
from bleak import discover, BleakClient, BleakScanner

MAC_ADDRESS = "TODO"

async def discover_devices():
    devices = await discover()
    for d in devices:
        print(f"- Found device {d.name} with address {d.address}")
        
async def print_services(mac_addr: str):
    device = await BleakScanner.find_device_by_address(mac_addr)
    async with BleakClient(device) as client:
        svcs = await client.get_services()
        print("Services:")
        for service in svcs:
            print(service)

loop = asyncio.get_event_loop()

loop.run_until_complete(discover_devices())
#loop.run_until_complete(print_services(MAC_ADDRESS))