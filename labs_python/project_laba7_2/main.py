import aiofiles
import os
import asyncio

async def read_file(filepath):
    async with aiofiles.open(filepath, mode='r', encoding='utf-8') as f:
        content = await f.read()
        return content
    
async def process_file(content, filepath):

    filename = os.path.basename(filepath)
    lines = content.split('\n')
    words = content.split()
    longest_word = max(words, key=len)

    return {
        'filename': filename,
        'lines': len(lines),
        'words': len(words),
        'characters': len(content),
        'longest_word': longest_word
    }

async def main():

    files = [
        '/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/project_laba7_2/data/file1.txt',
        '/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/project_laba7_2/data/file2.txt',
        '/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/project_laba7_2/data/file3.txt'
    ]

    stats = []

    for file in files:
        content = await read_file(file)
        stats.append(await process_file(content, file))

    for i in range(len(files)):
        print(f'\n{'='*50}')
        print(f'Filename: {stats[i]["filename"]}')
        print(f'Lines: {stats[i]["lines"]}')
        print(f'Words: {stats[i]["words"]}')
        print(f'Characters: {stats[i]["characters"]}')
        print(f'Longest word: {stats[i]["longest_word"]}')
        print(f'{'='*50}\n')

if __name__ == '__main__':
    asyncio.run(main())