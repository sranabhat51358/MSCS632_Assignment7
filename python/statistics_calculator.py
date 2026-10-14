
class StatisticsCalculator:
    """Calculate mean, median, and mode for a list of integers."""

    def __init__(self, numbers):
        if not numbers:
            raise ValueError("The list cannot be empty.")

        if any(
            isinstance(number, bool) or not isinstance(number, int)
            for number in numbers
        ):
            raise TypeError("All values must be integers.")

        self._numbers = numbers.copy()

    def calculate_mean(self):
        """Return the arithmetic mean."""
        return sum(self._numbers) / len(self._numbers)

    def calculate_median(self):
        """Return the middle value or the average of two middle values."""
        ordered = sorted(self._numbers)
        size = len(ordered)
        middle = size // 2

        if size % 2 == 1:
            return float(ordered[middle])

        return (ordered[middle - 1] + ordered[middle]) / 2.0

    def calculate_mode(self):
        """Return all values tied for the highest frequency."""
        frequencies = {}

        for number in self._numbers:
            frequencies[number] = frequencies.get(number, 0) + 1

        highest_frequency = max(frequencies.values())

        return sorted(
            number
            for number, frequency in frequencies.items()
            if frequency == highest_frequency
        )


def read_positive_count():
    while True:
        try:
            count = int(input("Enter the number of integers: "))

            if count > 0:
                return count

            print("Please enter a positive number.")
        except ValueError:
            print("Invalid input. Please enter an integer.")


def read_numbers(count):
    numbers = []

    while len(numbers) < count:
        position = len(numbers) + 1

        try:
            number = int(input(f"Enter integer {position}: "))
            numbers.append(number)
        except ValueError:
            print("Invalid input. Please enter an integer.")

    return numbers


def main():
    print("Python - Object-Oriented Statistics Calculator")

    count = read_positive_count()
    numbers = read_numbers(count)

    calculator = StatisticsCalculator(numbers)

    print("\nNumbers:", ", ".join(map(str, numbers)))
    print(f"Mean: {calculator.calculate_mean():.2f}")
    print(f"Median: {calculator.calculate_median():.2f}")
    print("Mode:", ", ".join(map(str, calculator.calculate_mode())))


if __name__ == "__main__":
    main()

