(define append1
  (lambda (a b)
    (letrec ((do-append1
              (lambda (a b)
                (if (null? a)
                  b
                  (do-append1 (cdr a) (cons (car a) b)) ))))
      (do-append1 (reverse a) b) )))


(define member?
  (lambda (e l)
    (cond
      ((null? l) #f)
      ((eqv? e (car l)) #t)
      (else (member? e (cdr l))) )))


(define member1
  (lambda (e l)
    (cond
      ((null? l) #f)
      ((eqv? e (car l)) l)
      (else (member1 e (cdr l))) )))


(define flatten
  (lambda (l)
    (letrec ((do-flatten
              (lambda (l r)
                (cond
                  ((null? l) r)
                  ((list? (car l)) 
                    (do-flatten 
                      (cdr l) 
                      (do-flatten (car l) r) ))
                  ((string? (car l)) 
                    (do-flatten 
                      (cdr l) 
                      (cons (string->symbol (car l)) r) ))
                  (else 
                    (do-flatten 
                      (cdr l) 
                      (cons (car l) r))) ))))
      (reverse (do-flatten l '())) )))


(define zip
  (lambda (a b)
    (letrec ((do-zip 
              (lambda (a b l)
                (if (or (null? a) (null? b))
                  l
                  (do-zip 
                    (cdr a) 
                    (cdr b)
                    (cons (list (car a) (car b)) l) )))))
      (reverse (do-zip a b '())) )))
