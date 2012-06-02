(define (id x) x)

(define (divisible-by-p n)
 (lambda (x) (= (modulo x n) 0)))

(define (<-p n)
  (lambda (x) (< x n)))

(define (or/p . preds)
 (lambda (val)
   (ormap (lambda (p) (apply p (list val))) preds)))

(define (upto n)
 (build-list n id))

(define (sum ls) (foldl + 0 ls))

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