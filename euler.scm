(define (id x) x)
(define (k x) (lambda _ x))

(define (divisible-by-p n)
 (lambda (x) (= (modulo x n) 0)))

(define (<-p n)
  (lambda (x) (< x n)))

(define (or/p . preds)
 (lambda (val)
   (ormap (lambda (p) (apply p (list val))) preds)))

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
      (map (lambda (y) (* x y)) l2))
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