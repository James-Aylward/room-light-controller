# Generates a C++ compatable string from html code


text = []

# Read the html file into line array
with open("root.html", 'r') as file_input:
    text = [x.rstrip() for x in file_input.readlines()]

# Escape any quotations
for i, line in enumerate(text):
    text[i] = line.replace('"', '\\"')

# Fix unicode characters
for i, line in enumerate(text):
    text[i] = line.replace('\\u', '\\\\u')
    pass

# Add start text
text[0] = f"String root_html = \"{text[0]}"

with open("root.h", 'w') as file_output:
    for x in text[:-1]:
        file_output.write(x + "\\n\\\n")
    file_output.write(f"{text[-1]}\";")