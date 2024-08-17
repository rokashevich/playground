import asyncio
import aiohttp

# List of hosts to check
hosts = [
    "http://host1/health",
    "http://host2/health",
    "http://host3/health",
    # Add more hosts here...
]

# Limit the number of concurrent requests
CONCURRENCY_LIMIT = 100

# Function to check the availability of a single host asynchronously
async def check_host(sem, session, host):
    async with sem:
        try:
            async with session.get(host, timeout=5) as response:
                if response.status == 200:
                    return (host, True)
                else:
                    return (host, False)
        except Exception as e:
            return (host, False)

# Function to periodically check all hosts
async def check_all_hosts(hosts, interval=60):
    sem = asyncio.Semaphore(CONCURRENCY_LIMIT)
    async with aiohttp.ClientSession() as session:
        while True:
            tasks = [check_host(sem, session, host) for host in hosts]
            results = await asyncio.gather(*tasks)
            for host, status in results:
                if status:
                    print(f"{host} is UP")
                else:
                    print(f"{host} is DOWN")
            print("Sleeping...\n")
            await asyncio.sleep(interval)

# Start checking hosts
async def main():
    await check_all_hosts(hosts, interval=60)

if __name__ == "__main__":
    asyncio.run(main())
