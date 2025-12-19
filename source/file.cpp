#include "util2/file.hpp"
#include "util2/C/file.h"
#include "util2/C/string.h"
#include <filesystem>


namespace util2 {


bool loadFile(
	const char*   path, /* filepath 													*/ 
	unsigned int* size, /* the size of the out array that was pre-allocated.            */
	char*		  out   /* Where to place the file contents (Buffer of Min-Size 'size') */
) {
	bool status = true;
	*size = 0;
	out = nullptr;

	status = status && util2_load_file(path, size, out);
	status = status && util2_load_file(path, size, out);
	return status;
}


/* 
	Thanks to: 
	https://stackoverflow.com/questions/2868680/what-is-a-cross-platform-way-to-get-the-current-directory 
*/
void current_path(
	unsigned int*  size, 
	char* 		   out
) {
	auto path     = std::filesystem::current_path().generic_u8string();
	auto pathsize = path.size();

	/* buffer too small */
	if(pathsize > *size || out == nullptr) {
		*size = pathsize;
		return;
	}
	util2_memcpy(out, path.c_str(), pathsize);
	return;
}


} /* namespace util2 */