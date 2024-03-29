#!/usr/bin/env python

systemAccounts = [
    'utrio.msig',
    'utrio.stake',
    'utrio.token',
    'utrio.resfee',
    'utrio.fee',
    'utrio.rand',
    'utrio.bank',
    'utrio.empty',
    'utrio.reward',
    'utrio.mfee',
]

resignAccounts = [
    'utrio.stake',
    'utrio.resfee',
    'utrio.fee',
    'utrio.empty',
    'utrio.reward',
    'utrio.mfee',
]

initialAccounts = [
    'root',
    'root1',
    'root2',
    'root3',
    'root4',
    'root5',
]

accounts = [
    "genesis",
    ".111",
    ".112",
    ".113",
    ".114",
    ".115",
    ".121",
    ".122",
    ".123",
    ".124",
    ".125",
    ".131",
    ".132",
    ".133",
    ".134",
    ".135",
    ".141",
    ".142",
    ".143",
    ".144",
]

sk_list = [
    "ded9c4bf8c8c0f3e7e37da2d552d761692a8233c8ed9267b659143a2fa0708b3bd8ef784cf372fc487e726e890d6f9b0c12e9b5da5b2f90eab13d0555a46b6cc",
    "f54525920bc0767f8ebbc7d37d6ae6f2fd3bc774cf672bb5283eeca6f407c2258bdcffa2ad4452150193078640465b3fbd3ec95fb8e96b6ae668b8437ee21ef7",
    "637373f757befafc38c5952b89e58b83baead97986beda564c3f24a27eabfdfe9d559949d364f893ae93bda40968493876bdd61f5e3eef891f3c8b4941e79ddf",
    "5b0288fa12d668181b0133f45da78c23a8af8208f81c7b3a53999b6e907fdea49d5895456173e1efffbcb8077c819df7a6bf4823f319fb941d2595896a5c4211",
    "7f9394070b52f20ff9c9b9944aa07f681eb8cf168e28a491293123d8bcfe71bb43a976a650bd1b4e0a3a083cc1c9f11681565e993e17a37361c5850ee7338f14",
    "a027845ecf7bf449c42322de5fa8357ac576f7cea3354469511cab56b11dd56a520b2920c0c777b4099bf166df37ed3cccdb95753feb9ab994eea9ed5637487c",
    "20854c1ffb4109fb3d2719d5a5182041ab87ce3fde9488eaf15852a0386a7a5035f32ddae352673de2a7d486160cdb42ebfb6be36f2e80af547df17ef4f95010",
    "65fa8d038cd562c44d3ee11af771e5e8a8b9786fc2b9868fe3aff4a42b84b31504c22888568e11d702c73daa0a204cdc338f5bb42c6b28c55285cc28a48199cb",
    "becd499ea22e7ba382a3745fdd5603e485e72d5aecf9721681ac7c33ce92a8a1e81fc590cfe76608753746e850f6788de1447d431eb060a24bc693337996389e",
    "0619c549364efd8b8c7511d67129f9bf0296efba628357b622094889996d02b8caf593a6c4a683ae378f3061395aee688449e1f223232db7f8f678d69f3f1262",
    "e49641f9f09445d3221a06b1e21f9ae80895eccdec6c01e30e79447ddc0dc1ff6b1396df4385afaef69ee14614c6823f96e48f85f126d7c9bdaee97d6710f5b8",
    "6e6d21bd346cf909063f6dbba3537590b8a55f5e6d1eac48a666601167841c82619cf76a10328b96a1e1f0e909ff7490f0443d82b7914eb1b8884d68d2736ab4",
    "8941b162dce2316a7a3d31e872ae4a4b864f2a8d23e9ef14fb3146d3ab53714f44216146ae90b5b6f394a505a25bed21edd7552b9df98a93d2c60609edc8d68b",
    "1360a9e4d0ee7684330271eaddd314532d9770424023d738d32c53a1ac575b96679c5f73933f74343c6792ccc3b93013850165a17f86ae34fc66cbcd00c13644",
    "fd3c49c9c463180e2b85b86b258d3b86d5f2711e82b302c91bc29a93e50b1aff3f384107c941f1f8872a6ef9e772a4d71ef40289b9dfad6e0c818720b167e94d",
    "2dea3ff5b9bca2462ff0427c758416b764f24e55ee93c9b1d05f0a9f0c0a22795ca130c02aa9ddc977c04aaad6b8da879c8e8f1d7b754702a2d6be79cd918fbf",
    "8b2858b069cd3466f2a6b1bb2a3e18e3bff9c8160227645c8afaa8a152455f728af6d57fd3bfb801a25439614e37a2a126c0654d25053c5978c086a7b2b5db14",
    "8ae8dde1e6cabc37bf9fee4e2d8b3bb2ae65e779ff50c2bf839f16bf66e25f5908e86431fd72f54b44afdac457d126f6eb5cf6bf6ba5414f26054d0e83dd4eec",
    "c27d6591d89b050bf6ac73512ee17953160605959f026d14fd7291d3d34f1c4b4cf669efc24dc4b0c298092f3108091756e40a758a070eda5cceb8577d9df425",
    "d3500ce3db05c027ceccecfb2238cbe0528b8ca2e0f2881f2f37d5b265b4e8f6bfe5316533468d1f6e3e7b382c89b31cdb8a47ca7b685d186f7706752742e798",
]

pk_list = [
    "bd8ef784cf372fc487e726e890d6f9b0c12e9b5da5b2f90eab13d0555a46b6cc",
    "8bdcffa2ad4452150193078640465b3fbd3ec95fb8e96b6ae668b8437ee21ef7",
    "9d559949d364f893ae93bda40968493876bdd61f5e3eef891f3c8b4941e79ddf",
    "9d5895456173e1efffbcb8077c819df7a6bf4823f319fb941d2595896a5c4211",
    "43a976a650bd1b4e0a3a083cc1c9f11681565e993e17a37361c5850ee7338f14",
    "520b2920c0c777b4099bf166df37ed3cccdb95753feb9ab994eea9ed5637487c",
    "35f32ddae352673de2a7d486160cdb42ebfb6be36f2e80af547df17ef4f95010",
    "04c22888568e11d702c73daa0a204cdc338f5bb42c6b28c55285cc28a48199cb",
    "e81fc590cfe76608753746e850f6788de1447d431eb060a24bc693337996389e",
    "caf593a6c4a683ae378f3061395aee688449e1f223232db7f8f678d69f3f1262",
    "6b1396df4385afaef69ee14614c6823f96e48f85f126d7c9bdaee97d6710f5b8",
    "619cf76a10328b96a1e1f0e909ff7490f0443d82b7914eb1b8884d68d2736ab4",
    "44216146ae90b5b6f394a505a25bed21edd7552b9df98a93d2c60609edc8d68b",
    "679c5f73933f74343c6792ccc3b93013850165a17f86ae34fc66cbcd00c13644",
    "3f384107c941f1f8872a6ef9e772a4d71ef40289b9dfad6e0c818720b167e94d",
    "5ca130c02aa9ddc977c04aaad6b8da879c8e8f1d7b754702a2d6be79cd918fbf",
    "8af6d57fd3bfb801a25439614e37a2a126c0654d25053c5978c086a7b2b5db14",
    "08e86431fd72f54b44afdac457d126f6eb5cf6bf6ba5414f26054d0e83dd4eec",
    "4cf669efc24dc4b0c298092f3108091756e40a758a070eda5cceb8577d9df425",
    "bfe5316533468d1f6e3e7b382c89b31cdb8a47ca7b685d186f7706752742e798",
]

bls_sk_list = [
    "26bf5ac96faa98fa97be285639d17fbca7d8f5ef", # genesis
    "46482e455c3e2779477091be5d6ba67a5f6ff89f",
    "586e7086be81d33c54e7daaabe5f5a9fc8d14118",
    "79ca2a22e771e6dbb405bbc261f4468341a08749",
    "4506e22878340d23b7afe0b116c85ad332bd4fae",
    "238e8bb88d8cb8249dc219cbfa8195118703d4d4",
    "703b4d3500a5fdb2f0ef1da13d46660e9a69215d",
    "7c5b69a7ec501648ec18d06cf757c5d15c083a2d",
    "0f796d11f77d01f18787f5348b51fde0b3c0157a",
    "200c1b2e9188d54e14ed7fb0d00fe7764cc1788a",
    "7282803fe60a62143af3e2b0684e893e5a579e6b",
    "4bf0a21d17bcfc6db270b1c70801b4e8514072f3",
    "38b61804a8a36848f288c565e2b59e3f98a25b4f",
    "4e3336bbc116c5c27ceb16e04bb517e8d2e0af83",
    "1f5e255775007587c178758808ab8f5c52b55f6c",
    "7b1225310fe5542dea3e22500501308e064a317f",
    "397ab25d652a906db0e2ded3f1c74947b3ddaed5",
    "48569bb409bfd6237ac9722bf84877c74a41817f",
    "2977b70b37f27f564f4fef268028c10265f66635",
    "4eb06d74cc306f910835476d16a0c159b3b79dfa",
]

bls_pk_list = [
    "149342d0565f1645e40cd5aaaba7c6a29589d9346adb9c78e990b9f0d111dd3f48f23910fd96cf1d888fd9e841e8bc54934a572058158ed43edb4bb97c5672ef01", # genesis
    "8cab44d5141ae29bfca4acce7853427fa53a15baca5302fa96898d1e78cf17b79faaffbc2d03a4f947c567c6b5c0e30eed9a34ff51cd6c8a45954ea08df6943001",
    "771d9ba978c67aa215bb90e7a862f7d1f8400bfd58316025f2ed08d211ee074997328472d22a212bc5a701b0a61d4dc80d51771fdceb999d56779e6eab12e86200",
    "4676a734a6e3993fdb2612a4fd7e7974e40ea597a1dfe90862cecf97d9c565d5f050a44e2a94846315d63077bb630e76d1f1b356aea2f2b6da9c9f00db50e0ab00",
    "49e274908c7b8ac329f76799e344db9408efb08eb54e2d5118f1a8928afd05f20386bf463c443bc8787d96a1e2c62e5c0fdc04a087d54c90c81838f99c743b4c01",
    "400d4608261ad637ea19ada8fa895efe44bf1becaf09b5be29bdefa54753329da5a7a4f95385188032e61f2f016ef1993dec672cb824121617efa2c8c44d6a6f00",
    "87e28f0f4ca8f64c9ca5feb0864fe1eeff2ce1e08abbb7f1033f4b29a892deeb438d11a052db30bda691f760c9a765ff22016f79e4b0806f73a61f857360e7f901",
    "57bb1c3e31ce9901718e7f2d56728b88ab76c1fdb99dafffed2169291b046394f408e7cc8b84609fce0f214327fd8769d01c39d7a166dc32775a30af7147dd3700",
    "83e0f5f6f31d14ae9942684b3def0ac1b5fd05a7885b1a18327b03ee0f0785bbfcc7e6834577734e95d13f8970ede181e4333c55ae34a459bf8681c62050de7e01",
    "07f83d3629b4fcfb1ab3821a20e5af1c59fbab3f420e177b2e44b2b50910d3f30b6a0889c013d38263823f0dc78614f64cb2594c6aaceaf9a544e68641b75af701",
    "200d1c6cd4ef2cb5d6abcaa7ee242790b36427be9fe3aca8eb5f78e3190e1bf06cec08c8f7fe83e8b794aa5636d9c988473084236f5a285dc6670bd07d9d99cb00",
    "31867bed41c38c9b7983cb7f9b950277f3c6183317d637d8eb2534db42d1f927e79f639cbbc8d76a792a3033c8f7435e8d1367384f07db08d041f9a1d64eef0b00",
    "217314779939eaba4ff146ed491bdb09c0d93e7d14fb88dbbc5d9605188f399beba9b406dd2aacaa652895cd4192d5f3b2bcf67df50c69b177f36b7e461ce67600",
    "1a267887804f3bded62a8befb45f93efe09f3248bce6e0f0e5bdb1d413366454e8cfb8ef031e63927657fa4873a2bad3179326b0a1fc95d676557418d9159f8c00",
    "1689dd3fe3fba0c91af7e3c62b79806b31b5a44a2eebe1ae7492ad6dd3e537f956527556e9b6c8748a9db6021ccb831225312a4f1e24ebaa4c0461e0fae82dac00",
    "84b652ad0374fd45f2d5d7f2268ca3abc7a0c31d05097364d043ce41edc521accc22da80fce2a886af1ea87341559836b686a385f74e6ef0ceeb18d6a917438c01",
    "067245577493c914bcf2a53efcb5af5631c54a4725adfa0d9d0cc2f495b6f60b409407918a336091a536d9816020042b8ce9c37dcebfe44147b2b45f67257d0b00",
    "6b920ef963f2455931c790fadffe3393674ced80eba185bbd5cecbe0a315c653d94fb1ff76178fb5f3ed901ec3821185258fc1cd315a1ce237323e0c3362f1c601",
    "98c096f5727e6828b9ca5e3a1b163a284deae5c397cd8cdff4e2912a360981f8b39df25f32ba00a221b9bbb263783541a069b03393c910af604a3d45f56cbe5800",
    "3b2216d1872875ae9d4c396e0a3a5ac8ffd5e915a4568822cf5c67b6235039666d016f69b9f5ba3884aa5a09fa3d2e473ad280a849ba16d539afbf52e1b5732801",
]

account_pk_list = [
    "UTR6CJ7HUTv7DABGKAgvcf9HxoK8nF2RkKwcDKbwoMhRF5iPLg1Vc",
    "UTR6bAwfYwri5StmBHKmNu6WPHtYfLFnv8MkMykobVfxKmpfkQvGQ",
    "UTR5BRFYRs3S9LY9yKcAnhPrtteYpP1FYTk3dCEmzNz3fixpNHppm",
    "UTR84XW5MDMF46xVxvgUdjL629LqvywwgBiCqdsHGLkwZEpwW7Sot",
    "UTR68hcFr4GfBSftqMYrn8t77NTffS1GbrjRcBTFdpoE2VPHHV6JZ",
    "UTR7EqJDP1NBrKDfh89yCnZy8FGGtb7imumnvAo1C4UczxzLa5H7k",
    "UTR83vFWsfMfLzinQGgxn4KN4YjKNWkNzMPYcZm9ddvaf3rUdft1i",
    "UTR8FYFXdNc3cLEAmm5CqR6KGBnBFrKYSxGumggyYobFXvg6Dge7w",
    "UTR7bxvQJpNpwvGmmaH1gNs7H6CBYTbbFkVNUv2yjnVHmLwaNAw5V",
    "UTR6FFDyH7S1RbJE3xst6BfTLajXVeaN1PbJRbWJivr4gbZMFRUHb",
    "UTR5eM6nWffwfsfMUyZ2t1rsHKJPVTn8SRhsXK6PBoiSgi3498qFY",
    "UTR6c1f7MaGLgEEUp7FYMyhDE8baLGpnUr1Rx1GniTEf7CvzHB4MM",
    "UTR8miQA18URRU6zxH1mM8G64AojgFbLVUXiUocJkPmZZqspKyqQE",
    "UTR7JqiUNLaQMTNuTu13FHgKi8V33SuvJ4gX2u1LS4ivezhS8Wh8x",
    "UTR5XJGAY53rm2mrBHJcQjWuJRkTCKfNGvq8bQ57fbrtR84DYHTmQ",
    "UTR7RGVzxcAYdmJHeppi54efFMzRXHPNAHzDnL7GW8Xipp54r7eGM",
    "UTR7PhuozXtQYkLapjYMr2ZimU6A9uFxrYLUUnwSakpo7ZCpxagit",
    "UTR6Wu6v4UFEPzgRet1mwDQhwypUrprxYyfKkvyMNFXNje3YxA9is",
    "UTR7cYJk4eiwGTFTx4K6fzotuqqsQ6onfndPXicCDfnZC4zD9Cq24",
    "UTR6xy5FKjyV4bBe1FXTN2VXeFE9f87L7bJGdhhdmiG2ERnFGdTTS",
]

account_sk_list = [
    "5KCD2CCy8CyX6HynyHRKJD2qeqj5tJNctvuEBQRuaCDYhqkwLB1",
    "5JbXkT2DP8HpwfaCRmSa3Qw2vH1pqnxfKGk5w8riUJUSVx7j1ir",
    "5J4fz4cApTLTZzqjKsFSdCYPUyDNcmSD2WsLRoPbGjSB8KBu7RL",
    "5JtW4GQmgFoLBWS1iLHX5vsomyhUm5wix1kbmHrKoi7CwnoqYoc",
    "5K6WWFBqkHP3gQRq1fedyv6g4jHhHk9SbNpFR21x2ssgi1qtirK",
    "5JGfMjfe1gt5jxkhpoCyo9BHw7Lp72RX7s5CvMDKyysQvDsHddf",
    "5HqKy1xfQkLzeqgjtmHHLEnWKBKHpXsr1ctokUiSnaq6mSpvVsg",
    "5JNZV17PRmNL316BXdE4pT1FXN6nVSAtHKV59eCouD1HqVJPDH4",
    "5KRh8oVKGU3s8JsxyhELi3XoJyqGf7XgR4RQwrBjV8vmdRnVgeP",
    "5Jg1tBd4mf5NdSNnLpXDaX9LwoR2pnQH9kEz4tiy7o1FEuE3t75",
    "5KeW7TEWdHh8XscyhwXU687RtPZYHKZ9XJDKkjLYt9WJyJT9GQv",
    "5KXkRE8HkssPUjeP8BFyNvVewg8ugpkqRowDsE3JuR7jN6iKi9q",
    "5JQxTFoTJqS5RsaRmAso6MLCV12NirqWGGcYubZFDWy4tiZjA8U",
    "5KUwMD33e1a8p5gra3ApGwTA2Q8GCuLusLYR1nRNBQ9pe5xLbXa",
    "5J8xCnffhxMVs9QkQQ61xbFpFz9n6L4uB8qgwdYAsAcJtLw7fNi",
    "5Kcof8etCY4tJhde3J31NbzBqmi9yBUiBpyW43xoZThhJ7nN5po",
    "5KDjPsTLcBNvhHsbJpN6mCvTRb8UXMaNsMcnB2mBSk9QohB7Kma",
    "5Ju1fwfd6VdW5v8y998bdAayZdaTKdeEh7HCNC9ijMvr3Pp8FkD",
    "5J8PtAQxZrB5UCK1xneea6dzxvF6h5DM5nRzq1ktoxVXozYxrFZ",
    "5KTVxmhkT64i11T6g5YmuX4sUFYEpqxf7mpjBPDf49qR4R6knUC",
]