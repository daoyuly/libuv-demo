#include <stdio.h>
#include <uv.h>

uv_fs_t open_req;
uv_fs_t _read;

static char buffer[1024];
static uv_buf_t iov;

void on_read(uv_fs_t *req) {
    printf("on_read\n");
    printf("%s\n",iov.base);
}
void on_open(uv_fs_t *req) {
    printf("%zd\n",req->result);
    iov = uv_buf_init(buffer, sizeof(buffer));
    uv_fs_read(uv_default_loop(), &_read, (int)req->result,
               &iov, 1, -1, on_read);
}
int main() {
    const char* path = "/Users/umu/Documents/code-repo/libuv-repo/hello/text.txt";
    uv_fs_open(uv_default_loop(), &open_req,path, O_RDONLY, 0, on_open);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_fs_req_cleanup(&open_req);
    return 0;
}