; ModuleID = 'BoltModule'
source_filename = "BoltModule"

define i32 @main() {
entry:
  %age = alloca i32, align 4
  store i32 21, ptr %age, align 4
  ret i32 0
}
