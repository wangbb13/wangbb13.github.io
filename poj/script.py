with open("test", "w") as f:
  for i in range(50):
    for j in range(i+1):
      f.write("* ")
    f.write("\n")
