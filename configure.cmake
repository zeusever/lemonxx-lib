include(CheckCXXSourceRuns)
include(CheckIncludeFileCXX)

check_cxx_source_runs("void test(int &&){}\n int main(){ return 0;}" LEMON_COMPILER_SUPPORT_RVALUE)

check_cxx_source_runs("struct __declspec(align(1)) test{char a;}; int main(){return 0;} " LEMON_COMPILER_SUPPORT_DECLSPEC_ALIGNED)

check_cxx_source_runs("struct __attribute__((__aligned__((1)))) test{char a;}; int main(){return 0;}" LEMON_COMPILER_SUPPORT_ATTRIBUTE_ALIGNED)

check_cxx_source_runs(" int main(){__is_abstract(int); return 0;}" LEMON_COMPILER_SUPPORT_IS_ABSTRACT)

check_cxx_source_runs(" int main(){__is_base_of(int,char); return 0;}" LEMON_COMPILER_SUPPORT_IS_BASE_OF)

check_cxx_source_runs(" int main(){__is_class(int); return 0;}" LEMON_COMPILER_SUPPORT_IS_CLASS)

check_cxx_source_runs(" int main(){__is_enum(int); return 0;}" LEMON_COMPILER_SUPPORT_IS_ENUM)

check_cxx_source_runs(" int main(){__is_pod(int); return 0;}" LEMON_COMPILER_SUPPORT_IS_POD)

check_cxx_source_runs(" int main(){__has_trivial_constructor(int); return 0;}" LEMON_COMPILER_SUPPORT_HAS_TRIVIAL_CONSTRUCTOR)

check_cxx_source_runs(" int main(){long long a = 0; return 0;}" LEMON_COMPILER_SUPPORT_LONGLONG)


