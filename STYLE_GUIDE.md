#Code style convention:
---------------------

1) **Hungarian notation:** it's a camel case in which every variable name is preceded by its type in three or less lowercase letters, sometimes four or five, if there aren't better options.

2) Function names should be `lowercase_with_underscores_where_spaces_should_be`, Python style, except when return boolean (`isSomething`) or getters and setters, those should be camel case.

3) Spaces before and after comparison, assignment, arithmetic and stream operators. **No** spaces inside parentheses, square and angle brackets or curly braces.

4) **Avoid curly braces whenever possible.** They must be always in a new line, so they **match** each other vertically, except when "inline" (the opening and closing ones at the same line). "`While`" also in a new line.

5) Pointer declaration asterisks stick to the **type** instead of the variable name. No space before, one space after.

6) Class names in lowercase, as short as possible, **only a single word** whenever possible. Otherwise, they will follow the convention for functions. Sorry, no camel case this time.

