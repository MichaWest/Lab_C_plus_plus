import time
import sys

def compute(x: float) -> float:
    return x*x - x*x + x*4 - x*5 + x + x

def main():
    while True:
        user_input = input("Enter number of iterations (or non-number to exit): ")
        try:
            n = int(user_input)
        except ValueError:
            print("Invalid input. Exiting.")
            break

        x = 1.0
        start = time.perf_counter()

        for _ in range(n):
            res = compute(x)

        end = time.perf_counter()
        print(f"Time taken: {end - start:.6f} seconds")

        again = input("Run again? (y/n): ").strip().lower()
        if again != 'y':
            break

if __name__ == "__main__":
    main()
