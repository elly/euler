(define (id x) x)

(define (divisible-by-p n)
 (lambda (x) (= (modulo x n) 0)))

(define (or/p . preds)
 (lambda (val)
   (ormap (lambda (p) (apply p (list val))) preds)))

(define (upto n)
 (build-list n id))

(define (sum ls) (foldl + 0 ls))

(define (solve-1)
 (sum
  (filter (or/p (divisible-by-p 3)
		(divisible-by-p 5))
	  (upto 1000))))