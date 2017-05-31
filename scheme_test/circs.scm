(display "rendering many circles") 
(newline)

(define color-id (rnt-id "color"))
(define circ-id (rnt-id "circ"))
(define fill-id (rnt-id "fill"))
(define rnd-id (rnt-id "pix_rnd"))

(define (color r g b) 
 (begin 
  (rnt-push r)
  (rnt-push g) 
  (rnt-push b) 
  (rnt-ex color-id)))

(define (circ x y d) 
 (begin 
  (rnt-push x)
  (rnt-push y)
  (rnt-push d)
  (rnt-ex circ-id)))

(define (fill) (rnt-ex fill-id))

(define (rnd mn mx) 
 (begin 
  (rnt-push mn)
  (rnt-push mx)
  (rnt-ex rnd-id)
  (rnt-pop)))

(define (one-circle)
 (begin
  (color 0.0 0.0 (rnd 0.1 1.0)) 
  (circ (rnd 0 300) (rnd 0 300) 20) 
  (fill)))

(define (many-circles n) 
 (if (= n 0) () 
  (begin (one-circle) (many-circles (- n 1)))))

(many-circles 5000)
