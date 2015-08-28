#include <iostream>
#include <cassert>
#include <tlsf.h>

void test_pool(tlsf_t tlsf) {
	size_t alloc_size = 2642080;
	std::cout << "test pool for " << std::hex << alloc_size << std::endl;
	size_t pool_size = alloc_size + tlsf_pool_overhead() + tlsf_alloc_overhead();
	void* memory = ::malloc(pool_size);
	pool_t pool = tlsf_add_pool(tlsf,memory,pool_size);
	void* ptr = tlsf_malloc(tlsf,alloc_size);
	tlsf_walk_pool(pool,0,0);
	assert(ptr);
	tlsf_free(tlsf,ptr);
	tlsf_remove_pool(tlsf,pool);
	::free(memory);
}

int main(int argc, char** argv) {
	size_t block_size = 1024;
	size_t size = block_size + tlsf_size() + tlsf_pool_overhead() + tlsf_alloc_overhead() * 4;
	void* memory = ::malloc(size);
	tlsf_t tlsf = tlsf_create_with_pool(memory,size);
	// eat all memory
	size_t cntr = 0;
	size_t alloc_size = 256;
	while (alloc_size >= 16) {
		while (void* ptr = tlsf_malloc(tlsf,alloc_size)) {
			++cntr;
		}
		alloc_size /= 2;
	}
	std::cout << "allocated " << cntr << " blocks" << std::endl;
	tlsf_check(tlsf);
	tlsf_walk_pool(tlsf_get_pool(tlsf),0,0);
	test_pool(tlsf);
	::free(memory);
	return 0;
}