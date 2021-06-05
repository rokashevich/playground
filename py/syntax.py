def d():
    def onDecorator(func):
        code = func.__code__

        def onCall(*pargs, **kargs):
            #print(code, code.co_varnames)
            print('open', pargs, end='')
            ret = func(*pargs, **kargs)
            print('close')
            return ret
        return onCall
    return onDecorator


@d()
def f(*pargs, **kargs):
    print('specific work:', pargs, kargs)


f(1, 2, a=3, b=4)
f(5, 6, c=7, d=8)


# def f1(*pargs):
#     print('f(*pargs) -> f(1, 2, 3) -> print(pargs) = кортеж:', pargs)
# def f2(**kargs):
#     print('f(**kargs) -> f(a=1, b=2, c=3) -> print(kargs) = словарь:', kargs)
# f1(1, 2, 3)
# f2(a=1, b=2, c=3)
