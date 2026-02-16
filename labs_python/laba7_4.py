import aiohttp
import asyncio



async def get_responce(session, url):
    try:
        async with session.get(url, timeout=5) as response:
            return response.status
    except aiohttp.ServerTimeoutError:
        return 'ERROR: Server timeout error'
    except aiohttp.ClientConnectorError:
        return 'ERROR: Connection error'
    except aiohttp.InvalidUrlClientError:
        return 'ERROR: Invalid URL'
    except Exception as e:
        return f'ERROR: Unexpected error {e}'
    
async def main():
    urls = [
    'https://www.google.com',
    'https://www.github.com',
    'https://несуществующий-сайт-12345.рф',
    'https://this-domain-definitely-does-not-exist-123.com',
    'not-a-valid-url',
    'http://',
    'http://httpbin.org/delay/10',
    ]

    async with aiohttp.ClientSession(connector=aiohttp.TCPConnector(ssl=False)) as session:
        tasks = [get_responce(session, url) for url in urls]
        results = await asyncio.gather(*tasks)

    for i in range(len(urls)):
        print(f'{urls[i]} status: {results[i]}')

if __name__ == '__main__':
    asyncio.run(main())