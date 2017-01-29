require 'GameObject'

a = GameObject:new{name = "obj1", x = 5, y = 3}
a:rename("obj2")

b = GameObject:get("obj2")

b:info()