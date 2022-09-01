import { constVal, buildCommonSetting } from "./const_val.js";

var json = [{
	"var":[
		{"sdkPath":constVal.sdkPath},
		{"clangPath":constVal.clangPath},
		{"srcPath":constVal.srcPath},
		{"ndkIncludePath":constVal.ndkIncludePath},
		{"ndkBinPath":constVal.ndkBinPath},
		{"v8dir": constVal.v8dir},
		{"targetDir": constVal.targetDir},
	],
	"compile":{
		"ccompiler":"${clangPath}/clang.exe",
		"cppcompiler":"${clangPath}/clang++.exe",
			
		"include":[
			"${sdkPath}/include/c++/7.2.0",
			"${sdkPath}/include/c++/7.2.0/include",
			//"C:/cygwin64/usr/local/x86_64-unknown-linux-gnu/lib/gcc/x86_64-unknown-linux-gnu/7.2.0/include", // sse is compile error
			"${ndkIncludePath}",
			"${sdkPath}/include/c++/7.2.0/x86_64-unknown-linux-gnu/",
			"${srcPath}",
			"${sdkPath}/sysroot/usr/include",
			"${sdkPath}/sysroot/usr/",
			"${sdkPath}/sysroot/usr/include/linux",
			"${srcPath}/linux",
			"${srcPath}/gen/${v8dir}/include",
			"${srcPath}/${v8dir}",
			"${srcPath}/${v8dir}/include",
			"${srcPath}/third_party/",
			"${srcPath}/third_party/zlib",
			"${srcPath}/node/openssl/openssl/include",
			"${srcPath}/node/openssl",
			"${srcPath}/node/uv/src",
			"${srcPath}/node/cares/include",
			"${srcPath}/node/cares/config/linux",
			"${srcPath}/node/uv/include"
		],
		"prebuildSrc":[
			//"${srcPath}/node/src/node_crypto.cc",
			///"${srcPath}/node/src/node_util.cc",
			"${srcPath}/node/src/tty_wrap.cc",
			//"${srcPath}/node/src/node_contextify.cc",
			"${srcPath}/node/src/node_javascript.cc",
			"${srcPath}/node/src/node_node.cc"
		],
		"src":[
			"${srcPath}/node/cares/src/bitncmp.c",
			"${srcPath}/node/cares/src/inet_net_pton.c",
			"${srcPath}/node/cares/src/inet_ntop.c",
			"${srcPath}/node/cares/src/windows_port.c",
			"${srcPath}/node/cares/src/ares__close_sockets.c",
			"${srcPath}/node/cares/src/ares__get_hostent.c",
			"${srcPath}/node/cares/src/ares__read_line.c",
			"${srcPath}/node/cares/src/ares__timeval.c",
			"${srcPath}/node/cares/src/ares_cancel.c",
			"${srcPath}/node/cares/src/ares_create_query.c",
			"${srcPath}/node/cares/src/ares_data.c",
			"${srcPath}/node/cares/src/ares_destroy.c",
			"${srcPath}/node/cares/src/ares_expand_name.c",
			"${srcPath}/node/cares/src/ares_expand_string.c",
			"${srcPath}/node/cares/src/ares_fds.c",
			"${srcPath}/node/cares/src/ares_free_hostent.c",
			"${srcPath}/node/cares/src/ares_free_string.c",
			"${srcPath}/node/cares/src/ares_getenv.c",
			"${srcPath}/node/cares/src/ares_gethostbyaddr.c",
			"${srcPath}/node/cares/src/ares_gethostbyname.c",
			"${srcPath}/node/cares/src/ares_getnameinfo.c",
			"${srcPath}/node/cares/src/ares_getopt.c",
			"${srcPath}/node/cares/src/ares_getsock.c",
			"${srcPath}/node/cares/src/ares_init.c",
			"${srcPath}/node/cares/src/ares_library_init.c",
			"${srcPath}/node/cares/src/ares_llist.c",
			"${srcPath}/node/cares/src/ares_mkquery.c",
			"${srcPath}/node/cares/src/ares_nowarn.c",
			"${srcPath}/node/cares/src/ares_options.c",
			"${srcPath}/node/cares/src/ares_parse_a_reply.c",
			"${srcPath}/node/cares/src/ares_parse_aaaa_reply.c",
			"${srcPath}/node/cares/src/ares_parse_mx_reply.c",
			"${srcPath}/node/cares/src/ares_parse_naptr_reply.c",
			"${srcPath}/node/cares/src/ares_parse_ns_reply.c",
			"${srcPath}/node/cares/src/ares_parse_ptr_reply.c",
			"${srcPath}/node/cares/src/ares_parse_soa_reply.c",
			"${srcPath}/node/cares/src/ares_parse_srv_reply.c",
			"${srcPath}/node/cares/src/ares_parse_txt_reply.c",
			"${srcPath}/node/cares/src/ares_platform.c",
			"${srcPath}/node/cares/src/ares_process.c",
			"${srcPath}/node/cares/src/ares_query.c",
			"${srcPath}/node/cares/src/ares_search.c",
			"${srcPath}/node/cares/src/ares_send.c",
			"${srcPath}/node/cares/src/ares_strcasecmp.c",
			"${srcPath}/node/cares/src/ares_strdup.c",
			"${srcPath}/node/cares/src/ares_strerror.c",
			"${srcPath}/node/cares/src/ares_timeout.c",
			"${srcPath}/node/cares/src/ares_version.c",
			"${srcPath}/node/cares/src/ares_writev.c",
			"${srcPath}/node/src/cares_wrap.cc",
			"${srcPath}/node/src/connect_wrap.cc",
			"${srcPath}/node/src/connection_wrap.cc",
			"${srcPath}/node/src/debug-agent.cc",
			"${srcPath}/node/src/env.cc",
			"${srcPath}/node/src/fs_event_wrap.cc",
			"${srcPath}/node/src/handle_wrap.cc",
			"${srcPath}/node/src/http_parser.c",
			"${srcPath}/node/src/js_stream.cc",
			"${srcPath}/node/src/node_api.cc",
			"${srcPath}/node/src/node_buffer.cc",
			"${srcPath}/node/src/node_config.cc",
			"${srcPath}/node/src/node_constants.cc",
			"${srcPath}/node/src/node_contextify.cc",
			"${srcPath}/node/src/node_crypto.cc",
			"${srcPath}/node/src/node_crypto_bio.cc",
			"${srcPath}/node/src/node_crypto_clienthello.cc",
			"${srcPath}/node/src/node_dtrace.cc",
			"${srcPath}/node/src/node_file.cc",
			"${srcPath}/node/src/node_http_parser.cc",
			"${srcPath}/node/src/node_i18n.cc",
			"${srcPath}/node/src/node_javascript.cc",
			"${srcPath}/node/src/node_node.cc",
			"${srcPath}/node/src/node_os.cc",
			"${srcPath}/node/src/node_revert.cc",
			"${srcPath}/node/src/node_stat_watcher.cc",
			"${srcPath}/node/src/node_url.cc",
			"${srcPath}/node/src/node_util.cc",
			"${srcPath}/node/src/node_v8.cc",
			"${srcPath}/node/src/node_watchdog.cc",
			"${srcPath}/node/src/node_zlib.cc",
			"${srcPath}/node/src/pipe_wrap.cc",
			"${srcPath}/node/src/process_wrap.cc",
			"${srcPath}/node/src/signal_wrap.cc",
			"${srcPath}/node/src/spawn_sync.cc",
			"${srcPath}/node/src/stream_base.cc",
			"${srcPath}/node/src/stream_wrap.cc",
			"${srcPath}/node/src/string_bytes.cc",
			"${srcPath}/node/src/string_search.cc",
			"${srcPath}/node/src/tcp_wrap.cc",
			"${srcPath}/node/src/timer_wrap.cc",
			"${srcPath}/node/src/tls_wrap.cc",
			"${srcPath}/node/src/tty_wrap.cc",
			"${srcPath}/node/src/udp_wrap.cc",
			"${srcPath}/node/src/util1.cc",
			"${srcPath}/node/src/uv.cc",
			"${srcPath}/node/src/async-wrap.cc",
			"${srcPath}/node/src/backtrace_posix.cc",
			"${srcPath}/node/src/node_counters.cc",
			//"${srcPath}/node/uv/src/unix/aix.c",
			"${srcPath}/node/uv/src/unix/async.c",
			"${srcPath}/node/uv/src/unix/core.c",
			"${srcPath}/node/uv/src/unix/dl.c",
			"${srcPath}/node/uv/src/unix/fs.c",
			"${srcPath}/node/uv/src/unix/getaddrinfo.c",
			"${srcPath}/node/uv/src/unix/getnameinfo.c",
			//"${srcPath}/node/uv/src/unix/kqueue.c",
			"${srcPath}/node/uv/src/unix/linux-core.c",
			"${srcPath}/node/uv/src/unix/linux-inotify.c",
			"${srcPath}/node/uv/src/unix/linux-syscalls.c",
			"${srcPath}/node/uv/src/unix/loop-watcher.c",
			"${srcPath}/node/uv/src/unix/loop.c",
			//"${srcPath}/node/uv/src/unix/netbsd.c",
			//"${srcPath}/node/uv/src/unix/openbsd.c",
			"${srcPath}/node/uv/src/unix/pipe.c",
			"${srcPath}/node/uv/src/unix/poll.c",
			"${srcPath}/node/uv/src/unix/process.c",
			"${srcPath}/node/uv/src/unix/proctitle.c",
			//"${srcPath}/node/uv/src/unix/pthread-barrier.c",
			"${srcPath}/node/uv/src/unix/pthread-fixes.c",
			"${srcPath}/node/uv/src/unix/signal.c",
			"${srcPath}/node/uv/src/unix/stream.c",
			"${srcPath}/node/uv/src/unix/tcp.c",
			"${srcPath}/node/uv/src/unix/thread.c",
			"${srcPath}/node/uv/src/unix/timer.c",
			"${srcPath}/node/uv/src/unix/tty.c",
			"${srcPath}/node/uv/src/unix/udp.c",
			"${srcPath}/node/uv/src/inet.c",
			"${srcPath}/node/uv/src/threadpool.c",
			"${srcPath}/node/uv/src/uv-common.c",
			"${srcPath}/node/uv/src/version.c",
			"${srcPath}/node/uv/src/fs-poll.c"
		],
		// 
		"cmd":[
			"-fno-exceptions",
			"--target=x86_64-linux-guneabi", 
			"-std=c++14",
			"-fms-extensions",
			//"-fshort-wchar",
			"-D__POSIX__=1",
			"-DHAVE_CONFIG_H",
			"-D_GNU_SOURCE",
			"-DUSE_AURA",
			"-DOS_LINUX_FOR_WIN",
			"-DINSIDE_BLINK",
			"-DBLINK_IMPLEMENTATION",
			"-DENABLE_WKE",
			"-D_HAS_CONSTEXPR=0",
			"-D_CRT_SECURE_NO_WARNINGS",
			"-DNODE_WANT_INTERNALS",
			"-DHAVE_OPENSSL",
			"-DCARES_STATICLIB",
			"-DBUILDING_UV_SHARED",
			"-DENABLE_NODEJS=1"
		],
		"objdir":"${srcPath}/out/tmp/nodejs/${targetDir}",
		"outdir":"${srcPath}/out/${targetDir}",
		"target":"libnodejs.a",
		"beginLibs":[
		],
		"linkerCmd":[],
		"endLibs":[
		],
		"linker":"${ndkBinPath}/ar.exe"
	}
}];

buildCommonSetting(json);
