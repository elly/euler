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
   (if (> d (/ n 2))
       #f
       (if (= (modulo n d) 0)
	   d
	   (loop (+ d 1))))))

(define (factorize n)
  (let ((f (find-factor n)))
    (if f
	(cons f (factorize (/ n f)))
	(list n))))

(define (max l) (argmax id l))

(define (palindrome? s)
  (if (< (string-length s) 2) #t
      (and (char=? (string-ref s 0)
		   (string-ref s (- (string-length s) 1)))
	   (palindrome? (substring s 1 (- (string-length s) 1))))))

(define (smallest p)
  (let loop ((n 0))
    (if (p n) n (loop (+ n 1)))))

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