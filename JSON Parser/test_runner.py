import os
import sys
from parser import validate_json

def run_tests(test_dir):
    """
    Runs all tests in the specified directory.
    """
    for filename in os.listdir(test_dir):
        if filename.endswith(".json"):
            filepath = os.path.join(test_dir, filename)
            with open(filepath, 'r') as file:
                data = file.read()
                print(f"Testing {filename}...")
                if validate_json(data):
                    print("  Valid JSON")
                else:
                    print("  Invalid JSON")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python test_runner.py <test_dir>")
        sys.exit(1)

    test_dir = sys.argv[1]
    run_tests(test_dir)
