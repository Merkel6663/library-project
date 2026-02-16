import aiofiles
import asyncio


#1
async def read_from_file(filename):
    async with aiofiles.open(filename, mode='r') as f:
        result = await f.read()
    return result


#3 
async def greatings(name):
    result = f'Привет, {name}'
    await asyncio.sleep(2)
    return result

async def main():
    names_list = ['Алена', 'Андрей', 'Максим', 'Дима']
    tasks = [greatings(names_list[1]), greatings(names_list[2]), greatings(names_list[3]), greatings(names_list[0])]
    results = await asyncio.gather(*tasks)
    
    
    print(results)


if __name__ == "__main__":
    asyncio.run(main())