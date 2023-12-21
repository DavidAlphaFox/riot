#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/bigarray.h>
#include <sys/uio.h>
#include <unistd.h>

CAMLprim value riot_unix_readv(value fd, value iovs, value count) {
    CAMLparam3(fd, iovs, count);
    
    int len = Int_val(count);
    struct iovec c_iovs[len];

    for (int i = 0; i < len; i++) {
        value iov = Field(iovs, i);
        c_iovs[i].iov_base = Caml_ba_data_val(Field(iov, 0));
        c_iovs[i].iov_len = Int_val(Field(iov, 1));
    }

    int ret = readv(Int_val(fd), c_iovs, len);
    if (ret == -1) caml_failwith("readv failed");

    CAMLreturn(Val_int(ret));
}
