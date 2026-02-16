import csv

with open('/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/train.csv', mode='r', encoding='utf-8') as file:
    reader = csv.DictReader(file)
    data = [row for row in reader]

sum_1 = 0
cabins_1 = []
cabins_uni_1 = set()
sum_2 = 0
cabins_2 = []
cabins_uni_2 = set()
sum_3 = 0
cabins_3 = []
cabins_uni_3 = set()
for row in data:
    if row['Embarked']:
        if row['Cabin']:
            if row['Embarked'] == 'C':
                cabins_1.append(row['Cabin'].split())
                for i in row['Cabin'].split():
                    cabins_uni_1.add(i)
            elif row['Embarked'] == 'Q':
                cabins_2.append(row['Cabin'].split())
                for i in row['Cabin'].split():
                    cabins_uni_2.add(i)
            elif row['Embarked'] == 'S':
                cabins_3.append(row['Cabin'].split())
                for i in row['Cabin'].split():
                    cabins_uni_3.add(i)

ans_1 = len(cabins_uni_1) / len(cabins_1)
ans_2 = len(cabins_uni_2) / len(cabins_2)
ans_3 = len(cabins_uni_3) / len(cabins_3)

print(f"C: {ans_1:.2f}")
print(f"Q: {ans_2:.2f}")
print(f"S: {ans_3:.2f}")