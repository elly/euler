(define (id x) x)
(define (k x) (lambda _ x))

(define (divisible-by-p n)
 (lambda (x) (= (modulo x n) 0)))

(define (<-p n)
  (lambda (x) (< x n)))

(define (or/p . preds)
 (lambda (val)
   (ormap (lambda (p) (p val)) preds)))

(define (upto n)
 (build-list n id))

(define (integers-in min max)
  (if (> min max) '()
      (cons min (integers-in (+ min 1) max))))

(define (square x) (* x x))

(define (sum ls) (foldl + 0 ls))
(define (product ls) (foldl * 1 ls))
(define (appearances ls n)
  (if (null? ls) 0
      (+ (if (= (car ls) n) 1 0)
	 (appearances (cdr ls) n))))
(define (uniqify ls)
  (if (null? ls) '()
      (cons (car ls)
	    (filter (lambda (x) (eq? x (car ls))) (cdr ls)))))
(define (most-appearances ls v)
  (appearances (argmax (lambda (x) (appearances x v)) ls) v
	       ))

(define (find-factor n)
 (let loop ((d 2))
   (if (> d (sqrt n))
       #f
       (if (= (modulo n d) 0)
	   d
	   (loop (+ d 1))))))

(define (factorize n)
  (let ((f (find-factor n)))
    (if f
	(cons f (factorize (/ n f)))
	(list n))))

(define (prime? n) (and (> n 1) (not (find-factor n))))

(define (max l) (argmax id l))

(define (palindrome? s)
  (if (< (string-length s) 2) #t
      (and (char=? (string-ref s 0)
		   (string-ref s (- (string-length s) 1)))
	   (palindrome? (substring s 1 (- (string-length s) 1))))))

(define (nth-smallest n p)
  (let loop ((c 0)
	     (i 0))
    (if (p i)
	(if (= c n) i
	    (loop (+ c 1) (+ i 1)))
	(loop c (+ i 1)))))
(define (smallest p)
  (nth-smallest 0 p))

; Crosses a pair of lists using function f. The result list contains (f x y) for
; all x in l1 and all y in l2.
(define (cross f l1 l2)
  (append*
   (map
    (lambda (x)
      (map (lambda (y) (f x y)) l2))
    l1)))

; A stream is represented as a single function which returns successive values
; of the stream.
(define (stream-take s n)
  (if (= n 0) '()
      (cons (s) (stream-take s (- n 1)))))

(define (stream-take-while s p)
  (let ((v (s)))
    (if (p v)
	(cons v (stream-take-while s p))
	'())))

(define (fib-stream)
  (let ((n0 0) (n1 1))
    (lambda ()
	   (let ((n (+ n0 n1)))
	     (set! n0 n1)
	     (set! n1 n)
	     n))))

; Problem 1: sum of integers below 1000 divisible by 3 or 5.
(define (solve-1)
 (sum
  (filter (or/p (divisible-by-p 3)
		(divisible-by-p 5))
	  (upto 1000))))

; Problem 2: sum of even-valued fibonacci sequence terms whose value is less
; than 4 million
(define (solve-2)
 (sum
  (filter even?
	  (stream-take-while (fib-stream) (<-p 4000000)))))

; Problem 3: Largest prime factor of 600851475143
(define (solve-3)
  (max (factorize 600851475143)))

; Problem 4: Largest palindrome that is the product of two 3-digit numbers
(define (solve-4)
  (max (filter (lambda (x) (palindrome? (number->string x)))
	       (cross * (upto 1000) (upto 1000)))))

; Problem 5: Smallest integer divisible by all of [1,20]
; Approach: factorize each of [1,20], and for each prime factor, choose the
; highest power.
(define (solve-5)
 (let* ((range (integers-in 1 20))
	(facts (map factorize range))
	(powers (map (lambda (f) (cons f (most-appearances facts f))) range)))
   (product
    (append*
     (map
      (lambda (fp)
	(build-list (cdr fp) (k (car fp))))
      powers)))
))

; Problem 6
(define (solve-6)
  (let ((range (integers-in 1 100)))
    (- (square (sum range))
       (sum (map square range)))))

; Problem 7
(define (solve-7)
  (nth-smallest 10000 prime?))

; Problem 8: Find the largest product of five consecutive digits in this string.
(define (solve-8)
  (let* ((num
	 "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450")
	(substrings (map (lambda (x) (substring num x (+ x 5)))
			 (integers-in 0 (- (string-length num) 5))))
	(sublists (map (lambda (x)
			 (map (lambda (c) (string->number (string c)))
			      (string->list x)))
		       substrings)))
    (max (map product sublists))))

; Problem 9: given a < b < c, a^2 + b^2 = c^2, and a + b + c = 1000,
; find a * b * c.
; Approach: Try each value of a up to 333. For each value of a, try each value
; of b from a up to 500; check if (= (+ a b c) 1000).

(define (good-triple? a b c)
  (= (+ a b c) 1000))

(define (good-pair? a b)
  (let ((c (sqrt (+ (square a) (square b)))))
    (if (= (floor c) c)
	(good-triple? a b c)
	#f)))

(define (solve-9)
  (let outer ((a 1))
    (let inner ((b a))
      (if (good-pair? a b)
	  (* a b (sqrt (+ (square a) (square b))))
	  (if (> b 500)
	      (if (> a 333)
		  #f
		  (outer (+ a 1)))
	      (inner (+ b 1)))))))

; Sum of all primes below 2000000.
(define (solve-10)
  (sum
   (filter prime? (upto 2000000))))

; Largest product of any four entries in this grid appearing in a line:
(define grid
  '((08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08)
    (49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00)
    (81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65)
    (52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91)
    (22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80)
    (24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50)
    (32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70)
    (67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21)
    (24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72)
    (21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95)
    (78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92)
    (16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57)
    (86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58)
    (19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40)
    (04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66)
    (88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69)
    (04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36)
    (20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16)
    (20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54)
    (01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48)))

(define (grid-cell g x y)
  (cond
   ((or (< x 0) (< y 0)) 0)
   ((or
     (>= x (length (car g)))
     (>= y (length g)))
    0)
   (else (list-ref (list-ref g x) y))))

(define directions
  '((-1 -1) (-1 0) (-1 1)
    (0  -1)        (0  1)
    (1  -1  (1  0) (1  1))))

(define (walk g x y d n)
  (if (= n 0) '()
      (cons (grid-cell g x y)
	    (walk g (+ x (first d)) (+ y (second d)) d (- n 1)))))

(define (all-walks g x y)
  (map
   (lambda (d) (walk g x y d 4))
   directions))

(define (best-walk g x y)
  (max (map product (all-walks g x y))))

(define (best-row-walk g x)
  (max
   (map (lambda (y) (best-walk g x y)) (upto (length (car g))))))

(define (solve-11)
  (max
   (map (lambda (x) (best-row-walk grid x)) (upto (length grid)))))