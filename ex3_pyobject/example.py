import library

print("=== Int ===")

# Works with numbers
c1 = library.Component()
c2 = library.Component()
c1.SetData(5)
c2.SetData(10)
print(c1 < c2)  # True

print("=== Str ===")

# Works with strings
c3 = library.Component()
c4 = library.Component()
c3.SetData("apple")
c4.SetData("banana")
print(c3 < c4)  # True

print("=== Custom object ===")

# Works with any object that defines __lt__
class Custom:
    def __init__(self, value):
        self.value = value
    def __lt__(self, other):
        return self.value < other.value

c5 = library.Component()
c6 = library.Component()
c5.SetData(Custom(1))
c6.SetData(Custom(2))
print(c5 < c6)  # True