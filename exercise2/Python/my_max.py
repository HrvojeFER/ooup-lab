def my_max(iterable, key):
  max_x = next(iter(iterable)) 
  max_key = key(max_x)

  for x in iterable:
    key_x = key(x)
    if key_x > max_key:
        max_x = x
        max_key = key_x

  return max_x

def my_max_main():
    print('max_int : %d' % my_max([1, 3, 5, 7, 4, 6, 9, 2, 0], lambda x: x))
    print('max_char: %c' % my_max("Suncana strana ulice", lambda x: x))
    
    print('max int: %s' % my_max([
      "Gle", "malu", "vocku", "poslije", "kise",
      "Puna", "je", "kapi", "pa", "ih", "njise"], lambda x: x))
    
    # I can use D.get here because it is already bound to the object D and therefore 
    # the interpreter inserts D as the self argument.
    D = {'burek':8, 'buhtla':5}
    print('max price: %s' % my_max(D, D.get))
    # I can bind the dictionary method get explicitly, if I want to.
    print('max price (explicit bind): %s' % my_max(D, lambda x: dict.get(D, x)))

    people = [('Ana', 'Ivić'), ('Ana', 'Sanjić'), ('Ivan', 'Ivić')]
    print('max person (by surname, then name): %s' % str(my_max(people, lambda x: x[1] + x[0])))
    print('max person (by name, then surname): %s' % str(my_max(people, lambda x: x[0] + x[1])))
