import csv

total_age = 0.0
count = 0

with open('/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/train.csv', 'r', encoding='utf-8') as f:
    reader = csv.DictReader(f)

    for row in reader:
        if row['Survived'] == '1':
            age_str = row['Age']

            if age_str:
                try:
                    age = float(age_str)
                    total_age += age
                    count += 1
                except ValueError:
                    continue

if count > 0:
    average = total_age / count
    print(f"{average:.2f}")
else:
    print("0.00")