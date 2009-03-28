Classes are organized using the class name instead of following a normal tree
because PHPUnit reporting doesn't understand folders, and ends up overwriting
a previous test report with a later test report if the last _* item in the
class names match.

