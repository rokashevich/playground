def singleton(cls):
    instances = {}

    def call(*kargs, **pargs):
        if not cls in instances:
            instances[cls] = cls(*kargs, **pargs)
        return instances[cls]
    return call


@singleton
class Person:
    def __init__(self, name):
        self.name = name


p1 = Person('John')
print(p1.name)
p2 = Person('Bob')
print(p2.name)

# class A:
#     def __init__(self):
#         self.a = 1

#     def __getattribute__(self, name):
#         # print(self.name)
#         print(object.__getattribute__(self, name))


# a = A()
# a.a

# class Descriptor:
#     def __get__(self, instance, owner):
#         print('get', instance, owner)

#     def __set__(self, instance, value):
#         print('set', instance, value)


# class A:
#     a = Descriptor()


# a = A()
# a.a
# a.a = 1
# class A:
#     def __init__(self, name):
#         self._name = name

#     # @property
#     def name(self):
#         print('fetch...')
#         return self._name
#     name = property(name)

#     @name.setter
#     def name(self, value):  # sname
#         print('change...')
#         self._name = value
#     # name = name.setter(sname)


# a = A('name1')
# print(a.name)
# a.name = 'name2'
# print(a.name)

# class E(Exception):
#     pass


# def bad():
#     raise E()


# try:
#     pass  # bad()
# except E:
#     print('E!')
# except Exception:
#     print('All but system')
# else:
#     print('no E')
# finally:
#     print('Finally')

# class B:
#     def __init__(self):
#         print('B')


# class D(B):
#     def __init__(self):
#         print('D')
#         super().__init__()


# d = D()
# class B:
#     def f(self):
#         print('B')


# class D(B):
#     def f(self):
#         # B.f(self)
#         super().f()


# d = D()
# d.f()

# def decorator(cls):
#     class Decorated:
#         counter = 0

#         def __init__(self, *pargs, **kargs):
#             self.warped = cls(*pargs, **kargs)
#             Decorated.counter += 1
#             print(Decorated.counter)

#         def __getattr__(self, name):
#             print('decorated get', name)
#             return getattr(self.warped, name)
#     return Decorated


# @decorator
# class C:
#     c = 123


# c1 = C()
# c2 = C()
# c3 = C()
# print(c2.c)

# def decor(f):
#     def call(*pargs, **kargs):
#         call.count += 1
#         print('decor', call.count, pargs, kargs)
#         return f(*pargs, **kargs)
#     call.count = 0
#     return call


# class C:
#     @decor
#     def f(self, *kargs, **pargs): print('Cf')


# c1 = C()
# c1.f(1, 2, 3)
# c1.f()

# c2 = C()
# c2.f()
# c2.f()


# class A:
#     def smet():
#         print('smet')
#     smet = staticmethod(smet)

#     @classmethod
#     def cmet(cls):
#         print(cls)


# class D(A):
#     pass


# a = D()
# a.cmet()
# class A:
#     def __get__(self, instance, owner):
#         return 40

#     def __set__(self, instance, value):
#         instance._some = value


# class B:
#     b = A()


# b = B()
# print(b.b)
# b.b = 14
# print(b.b)

# class A:
#     def getta(self):
#         return 777
#     a = property(getta, None, None, 'xxx')


# a = A()
# print(a.a)


# class B:
#     pass


# class C:
#     b = 2
#     __slots__ = ['a']

#     def __setattr__(self, name, value) -> None:
#         print('setattr', name)
#         return super().__setattr__(name, value)
#     pass


# c = C()
# c.a = 44
# print(c.a)
# def f(a, b, c, e=True, f=None, *pargs, **kargs):
#    x = 1
#    y = 2


# print('f.__code__             ->', f.__code__)
# print('f.__code__.co_nlocals  ->', f.__code__.co_nlocals)
# print('f.__code__.co_varnames ->', f.__code__.co_varnames)
# print('f.__code__.co_argcount ->', f.__code__.co_argcount)

# -----------------------------------------------------------------------------

# def d():
#     def onDecorator(func):
#         code = func.__code__
#         def onCall(*pargs, **kargs):
#             #print(code, code.co_varnames)
#             print('open', pargs, end='')
#             ret = func(*pargs, **kargs)
#             print('close')
#             return ret
#         return onCall
#     return onDecorator
# @d()
# def f(*pargs, **kargs):
#     print('specific work:', pargs, kargs)
# f(1, 2, a=3, b=4)
# f(5, 6, c=7, d=8)


# def f1(*pargs):
#     print('f(*pargs) -> f(1, 2, 3) -> print(pargs) = кортеж:', pargs)
# def f2(**kargs):
#     print('f(**kargs) -> f(a=1, b=2, c=3) -> print(kargs) = словарь:', kargs)
# f1(1, 2, 3)
# f2(a=1, b=2, c=3)

# def f(*pargs, **kargs):
#     print(pargs, kargs)
# f(1, 2, 3, 4, 5)
# f(1, 2, a=3, b=4, c=5)
