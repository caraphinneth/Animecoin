# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

BITCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBBITCOIN_SERVER=libanimecoin_server.a
LIBBITCOIN_COMMON=libanimecoin_common.a
LIBBITCOIN_CONSENSUS=libanimecoin_consensus.a
LIBBITCOIN_CLI=libanimecoin_cli.a
LIBBITCOIN_UTIL=libanimecoin_util.a
LIBBITCOIN_CRYPTO_BASE=crypto/libanimecoin_crypto_base.a
LIBBITCOINQT=qt/libanimecoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libanimecoin_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBBITCOINCONSENSUS=libanimecoinconsensus.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libanimecoin_wallet.a
endif

LIBBITCOIN_CRYPTO= $(LIBBITCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBBITCOIN_CRYPTO_SSE41 = crypto/libanimecoin_crypto_sse41.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBBITCOIN_CRYPTO_AVX2 = crypto/libanimecoin_crypto_avx2.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_AVX2)
endif
if ENABLE_AVX512
LIBBITCOIN_CRYPTO_AVX512 = crypto/libanimecoin_crypto_avx512.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_AVX512)
endif
if ENABLE_SHANI
LIBBITCOIN_CRYPTO_SHANI = crypto/libanimecoin_crypto_shani.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

	
# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
$(LIBBITCOIN_CRYPTO) \
$(LIBBITCOIN_UTIL) \
$(LIBBITCOIN_COMMON) \
$(LIBBITCOIN_CONSENSUS) \
$(LIBBITCOIN_SERVER) \
$(LIBBITCOIN_CLI) \
$(LIBBITCOIN_WALLET) \
$(LIBBITCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBBITCOINCONSENSUS)

bin_PROGRAMS =
TESTS =

if BUILD_BITCOIND
  bin_PROGRAMS += animecoind
endif

if BUILD_BITCOIN_UTILS
  bin_PROGRAMS += animecoin-cli animecoin-tx
endif

.PHONY: FORCE
# animecoin core #
BITCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  auxiliaryblockrequest.h \
  alert.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/params.h \
  core_io.h \
  core_memusage.h \
  crypto/sph_types.h \
  crypto/sph_blake.h \
  crypto/sph_groestl.h \
  crypto/sph_keccak.h \
  crypto/sph_bmw.h \
  crypto/sph_jh.h \
  crypto/sph_skein.h \
  wallet/db.h \
  hashblock.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  primitives/block.h \
  random.h \
  randomenv.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/register.h \
  rpc/server.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  wallet/crypter.h \
  wallet/rpcwallet.h \
  wallet/walletdb.h \
  wallet/wallet.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h\
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libanimecoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between animecoind and animecoin-qt
libanimecoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libanimecoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  alert.cpp \
  auxiliaryblockrequest.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/ismine.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  $(BITCOIN_CORE_H)

if ENABLE_ZMQ
libanimecoin_zmq_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libanimecoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif

# wallet: shared between animecoind and animecoin-qt, but only linked
# when wallet enabled
libanimecoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libanimecoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(BITCOIN_CORE_H)

# crypto primitives library
crypto_libanimecoin_crypto_base_a_CFLAGS = -fPIC
crypto_libanimecoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_CONFIG_INCLUDES)
crypto_libanimecoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libanimecoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/skein.c \
  crypto/sph_types.h \
  crypto/sph_blake.h \
  crypto/sph_groestl.h \
  crypto/sph_keccak.h \
  crypto/sph_bmw.h \
  crypto/sph_jh.h \
  crypto/sph_skein.h

if EXPERIMENTAL_ASM
crypto_libanimecoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libanimecoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libanimecoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libanimecoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libanimecoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libanimecoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libanimecoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libanimecoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libanimecoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libanimecoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libanimecoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libanimecoin_crypto_avx512_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libanimecoin_crypto_avx512_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libanimecoin_crypto_avx512_a_CXXFLAGS += $(AVX512_CXXFLAGS)
crypto_libanimecoin_crypto_avx512_a_CPPFLAGS += -DENABLE_AVX512
crypto_libanimecoin_crypto_avx512_a_SOURCES = crypto/sha256_avx512.cpp

crypto_libanimecoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libanimecoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libanimecoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libanimecoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libanimecoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libanimecoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libanimecoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_consensus_a_SOURCES = \
  amount.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/bitcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between animecoind, and animecoin-qt and non-server tools
libanimecoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libanimecoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  pow.cpp \
  primitives/block.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libanimecoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libanimecoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_util_a_SOURCES = \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  arith_uint256.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  fs.cpp \
  random.cpp \
  randomenv.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  support/lockedpool.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilstrencodings.cpp \
  utilmoneystr.cpp \
  utiltime.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libanimecoin_util_a_SOURCES += compat/glibc_compat.cpp
libanimecoin_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between animecoin-cli and animecoin-qt
libanimecoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libanimecoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libanimecoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libanimecoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# animecoind binary #
animecoind_SOURCES = bitcoind.cpp
animecoind_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
animecoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
animecoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
animecoind_SOURCES += bitcoind-res.rc
endif

animecoind_LDADD = \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

animecoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# animecoin-cli binary #
animecoin_cli_SOURCES = bitcoin-cli.cpp
animecoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
animecoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
animecoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
animecoin_cli_SOURCES += bitcoin-cli-res.rc
endif

animecoin_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CRYPTO) \
  $(BOOST_LIBS) \
  $(EVENT_LIBS)
#

# animecoin-tx binary #
animecoin_tx_SOURCES = bitcoin-tx.cpp
animecoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
animecoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
animecoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

animecoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(EVENT_LIBS)
#

# bitcoinconsensus library #
if BUILD_BITCOIN_LIBS
include_HEADERS = script/bitcoinconsensus.h
libanimecoinconsensus_la_SOURCES = $(crypto_libanimecoin_crypto_base_a_SOURCES) $(libanimecoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libanimecoinconsensus_la_SOURCES += compat/glibc_compat.cpp
  libanimecoinconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

libanimecoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libanimecoinconsensus_la_LIBADD = $(LIBSECP256K1)
libanimecoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libanimecoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
