from numpy import sin, linspace, pi, exp
from scipy import fft, arange, ifft
from Queue import Queue

N = 5

def sinus(Fs):
    Ts = 1.0/Fs; # sampling interval
    t = arange(0,1,Ts) # time vector

    ff = 5;   # frequency of the signal
    y = sin(2*pi*ff*t) #signal
    return y

def make_coeffs():
    return [ exp( 2 * pi * 1j * i / N) for i in xrange(N) ]

def make_icoeffs():
    return [ exp( 2 * pi * 1j * i / N) for i in xrange(N) ]

def lib():
    y = sinus(N)
    #print y
    transformed = fft(y)
    #print [x.real for x in transformed]
    inverse = ifft(transformed)
    #print [x.real for x in inverse]

def sdft(new, freq, coeffs):
    sdft.samples.put(new)
    old = sdft.samples.get()

    for i in xrange(len(freq)):
        freq[i] = (freq[i] + new - old) * coeffs[i]

    return freq

def isdft(freq, coeffs): 
    
    s = 0

    for i in range(len(freq)):
        s += freq[i] * coeffs[i]

    return s / len(freq)

def main():

    lib()

    freq = [0 for x in xrange(0,N)]

    sdft.d = 0;
    sdft.samples = Queue()

    isdft.d = 0;
    
    coeffs = make_coeffs()
    #samples = [1,2,3,4,5]

    for i in xrange(0,N):
        sdft.samples.put(0)

    for i in range(20):
        sdftres = sdft(i, freq, coeffs)
        print isdft(freq, coeffs).real

    
    
if (__name__ == "__main__"):
    main()
