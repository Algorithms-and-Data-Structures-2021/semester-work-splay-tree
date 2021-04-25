import matplotlib.pyplot as plt

if __name__ == '__main__':
    plt.figure(figsize=(10, 10))
    plt.xlabel('elements')
    plt.ylabel('time(µs)')
    operation = str(input())
    ox = [100, 500, 1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000, 2500000, 5000000]
    if operation == 'remove':
        oy = [12.57, 86.12, 217.07, 1428.04, 3358.01, 10402.94, 24529.08, 62695.43, 234452.42, 598181.25, 1530410.00,
            5012860.00, 12045210.00]
        plt.title('remove')
        plt.plot(ox, oy)

    if operation == 'insert':
        oy = [58.75, 242.61, 462.58, 2633.95, 5439.71, 14756.11, 35263.11, 79928.70, 253441.84, 607762.14,
              1403230.00, 4137390.00, 8561870.00]
        plt.title('insert')
        plt.plot(ox, oy)

    if operation == 'search':
        oy = [71.69, 508.86, 613.16, 2935.28, 6307.20, 18557.58, 43231.63, 101145.21, 309374.37, 309374.37,
              1579580.00, 4310460.00,	10076320.00]
        plt.title('search')
        plt.plot(ox, oy)

    plt.show()
