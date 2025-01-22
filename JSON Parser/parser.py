import json
import sys

def validate_json(data):
    """
    Validates JSON data by checking structure, key types, and value types.
    """
    def is_valid_value(value):
        # Validate values: string, int, float, bool, null, object, or array
        if isinstance(value, (str, int, float, bool, type(None))):
            return True
        if isinstance(value, dict):
            return all(isinstance(k, str) and is_valid_value(v) for k, v in value.items())
        if isinstance(value, list):
            return all(is_valid_value(item) for item in value)
        return False

    try:
        parsed = json.loads(data)  # Parse JSON string
        if isinstance(parsed, dict):  # Ensure it's a JSON object
            return all(isinstance(key, str) and is_valid_value(value) for key, value in parsed.items())
    except json.JSONDecodeError:
        return False  # Invalid JSON structure
    return False

if __name__ == "__main__":
    # Command-line interface for the JSON parser
    if len(sys.argv) != 2:
        print("Usage: python parser.py <file>")
        sys.exit(1)

    filename = sys.argv[1]
    try:
        with open(filename, 'r') as file:
            data = file.read()
        if validate_json(data):
            print("Valid JSON")
            sys.exit(0)
        else:
            print("Invalid JSON")
            sys.exit(1)
    except Exception as e:
        print(f"Error reading file: {e}")
        sys.exit(1)
