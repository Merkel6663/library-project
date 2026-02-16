import csv

with open('/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/train.csv', mode='r', encoding='utf-8') as file:
    reader = csv.DictReader(file)
    data = [row for row in reader]

sum_1 = 0
surv_1 = 0
sum_2 = 0
surv_2 = 0
sum_3 = 0
surv_3 = 0
for row in data:
    if row['Pclass']:
        if row['Pclass'] == '1':
            sum_1 += 1
            if row['Survived'] == '1':
                surv_1 += 1
        elif row['Pclass'] == '2':
            sum_2 += 1
            if row['Survived'] == '1':
                surv_2 += 1
        elif row['Pclass'] == '3':
            sum_3 += 1
            if row['Survived'] == '1':
                surv_3 += 1

ans_1 = surv_1 / sum_1 * 100
ans_2 = surv_2 / sum_2 * 100
ans_3 = surv_3 / sum_3 * 100

print(f"{ans_1:.2f}")
print(f"{ans_2:.2f}")
print(f"{ans_3:.2f}")