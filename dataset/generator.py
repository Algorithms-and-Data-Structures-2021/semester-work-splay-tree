import csv
import random
import time
import os

if __name__ == '__main__':
    os.chdir('data')
    folders1 = ['insert', 'remove', 'search']
    folders2 = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '09', '10']
    datas = [100, 500, 1000, 5000, 10000, 25000, 50000, 100000,
            250000, 500000, 1000000, 2500000, 5000000]
    for a in folders1:
        try:
            os.mkdir(a)
        except FileExistsError:
            pass
        os.chdir(a)
        for b in folders2:
            try:
                os.mkdir(b)
            except FileExistsError:
                continue
            os.chdir(b)
            for i in datas:
                FILENAME = f'{i}.csv'
                with open(FILENAME, "w", newline="") as file:
                    dataset = csv.writer(file)
                    for i in range(i):
                        dataset.writerow([random.randint(0, i)])
            os.chdir('..')
        os.chdir('..')

    print('Done')
