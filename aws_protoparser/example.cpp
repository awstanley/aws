#include <ConfigProtoV2.pb.h>

#include <aws_protoparser.hpp>

#include <iostream>

int main(int argc, char **argv) {

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	atexit(::google::protobuf::ShutdownProtobufLibrary);

	ConfigV2 cfg2;

	printf("raw argc/argv dump\nargc: %i; argv:\n", argc-1);
	for (int i = 1; i < argc; i++) {
		printf("% 3i - '%s'\n", i, argv[i]);
	}
	printf("\n\n");

	aws::protocolparser::Parse(argc, argv, &cfg2, true);

	std::string dump = aws::protocolparser::Dump(&cfg2);

	printf("%s\n", dump.c_str());

	int32_t enum_value = aws::protocolparser::GetEnum(&cfg2, "EnumTest", 0);
	printf("enum_value: %i (%s)\n", enum_value,
		aws::protocolparser::GetEnumAlias(&cfg2, "EnumTest", enum_value).c_str()
	);

	return 0;
}