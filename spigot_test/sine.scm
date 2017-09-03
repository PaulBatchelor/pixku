(ps-import "notes" "notes")
(ps-talias "nn" 0 "notes")
(ps-eval 0 
 (string-append 
 "_nn get mtof 0.5 1 1 1 fm " 
 "tick _offtick fe + tog 0.001 0.1 0.9 0.4 adsr dup " 
 "0.003 1 thresh _noteoff fe * "))
