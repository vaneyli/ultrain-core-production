#!/usr/bin/env python

bls_sk_list = [
    "26bf5ac96faa98fa97be285639d17fbca7d8f5ef", # genesis
    "62c990abff597f0133b8d3090a4533031d245b4e",
    "00bb28c715f3ec3ccb6baf7d96b82fcefcb08e82",
    "7b42b698cce9d34a3c3bdb0f7a31c5e32992a641",
    "68371a064f508d22aa2895dc588c0e248004b4fa",
    "04451c8370ea1526ce681705f9e9b32df44d7c32",
    "6016cec05f36d65dc2add045d1b405cb90c1ae69",
    "6a0d2abeffa9c3e418bd2c1b45808dec316898f9",
    "1ee7bf31c9322bbcfc5f7c3265dfab82d344de22",
    "6bbd5493a49e1c53b7c9105245aae097297ea175",
    "25543092ed6c59afbd0fb0cc182e68179062fe3f",
    "4211dfca2fe9a1ba504712d0ec038b6582b96b02",
    "5ebef5f782a346fc61510b0899a61dc326ac545e",
    "2574a51ba47df4abbfd0e5b07f47c17682325453",
    "4c2e839c8929bad1e60302e7d74b98c13d7e2af0",
    "2fbc9bb2812ce7d28ec48c12dd711a683cce963b",
    "74c48595142f5e0b3fb218300801c0418c0db933",
    "66c16b102252b07152c7c6ff1ed4973aa7f47799",
    "312ff1bbfbd98797ac506e742230bbdc6bd29c28",
    "335c3074dd2b1a2587209ad87afc105b1f2c38e7",
    "7cbe20b275eb3c7319a0e3ed8f0eab878f4ef5e5",
    "17cca19cb84720c52f3f017b4e539ab4cf36b3ca",
    "27ccd817a01bbff94700d67dca9b756b37207a66",
    "4314bc912286241bd8e73daebd8e3e0a717d9b79",
    "43684705ce4123778edbf6abf68427c027449afe",
    "60f4d499cb70e6f8f6cd7cc9c4c47d706b95fcf4",
    "41a2afdd36c44faf23635b8ea737e23a62aeecec",
    "15f727e30174d86060571a548f13c1dbc689e5f1",
    "0b65ff0dbd1e19a620f6977c93d1e8e13c5b64e6",
    "55e9a6a3142b0c5c23bb24e1113c04745784761d",
    "214e2f1ec6ee81c5d4ee71d34cb355771c4b46d4",
    "66d65c12b3b4b4b689e5db639605065d2a484259",
    "67df20fdaa173064e67984d7551b43387ad30291",
    "6e579a3471b3971c3a48816d155ca32d5fe3b439",
    "53a5f510bed11d2b4ec098a39b3fef9755458621",
    "3d6358776845dc413b0e02dd27c09ead20a7ef12",
    "1e074a9a7f02338baaf6fca511395ab69aa027e6",
    "6556cd8daf09a134b8436b89c6ffe5f612642603",
    "19b1416eddc63eebc15f3c4faa59d6cc23764595",
    "42900800b4191b608fbc772111a746aa5a9daef8",
    "67e650ca994c9bfe537a3d629f08f875085fa377",
    "6aef375599d231102b09ecc82dc6a05c3de312f6",
    "368aa0a7371aa4e1136108dd6cdf8e1f500d44e9",
    "3cd33817e17786987d8a873bcbbb99139eedaf02",
    "798c29b2d2c3f7f75064977495cfa8dd5d15639d",
    "7dd7b8157332ff91507ef2f80ec379d1b375c17c",
    "4587eafcf7c2962da2c52f6a27fda19af84f63db",
    "0428f90a03ef0c704875ec2a48ab43f0eda452b5",
    "6f8bd9ce5e1c2e00f8773a673fc6c8e5ab2f6ba3",
    "7b1a27e25f5f0b86205f67c40eccc315364c94af",
    "4c8cc9a79c1fb018529e50514a30b82461cbb764",
    "314213c91ae47688f443be266fe4a1a9252d0046",
    "6c11b0c9b8bc9c5cc9409feba7ebaffebf253a19",
    "501a5fc1c38d7098d985d994228e89086f852438",
    "0ded86cf78fc73a40e66ae4f05d9d5d054d796e4",
    "2b89dd195aaf180e4133fefc6d0d209b2f304619",
    "46023631e3b1fe3ab224838b266e466400aea971",
    "6fe56c70de18159a6ffdbddfa995145eea778fc5",
    "15d73fd081b36b194acf3bf7217771ebe26d904b",
    "7aede7dbf0c503507bc83c4aecdd5152d2faa222",
    "2681be961951e11aaa661e9dece5affdf8c4e545",
    "0741dff1229a0e5c753872f88ba22290c3c3609f",
    "22f49718d90ded419c88c25aabb4908830fc9337",
    "0418fc82de511c194f89672092624832e775ac1d",
    "5aad391ff79acdddab5bafea4002cbc0a8684dd8",
    "02a314c20f1de462edb370a6f89a64ba12959cd7",
    "25621611a9865d07ef5e15953f2efc005011bef8",
    "33b81a72ddcdd7457203c033efcffdf01cdeb930",
    "6045c2ed76ec160c640f405dd6317bbdf93fccb3",
    "518705c2382ccf4f92c0ba37034ec832070aa7b6",
    "6271d6e43449fcee6778980e1ce0585396ad2e01",
    "48164cda6a85cd6e06fcc2f852be262979c2705f",
    "7f536a63c6977f572e2a6b62c7d4df180252a6ad",
    "2582e63561c1907a269e751bb4c45647f83a4a37",
    "22faf1cb68b438a0143763e5a15e7a26b0ff7e8c",
    "7da66d9f7695eae967a6da72f6d334162ed9a660",
    "313a10298df735e8014f310c6bfddfc7d41a4453",
    "33b8f20dcbfb289db1e60efe45d4b742bc10b86b",
    "69238a306ec0b28a28898e0f539bb46a6d515c73",
    "23472481126b8e13fed4045c275b1d4150a40fc4",
    "277958acd8316aa540b7daa223f70a5c2aaf0ef2",
    "6ed98fbfc7a9e31f547d32a0b04026a071f2a9bb",
    "1caa4482abe1cb835673d44d8e136773fe8928bc",
    "211a603891991a990d86c270df17ea883c1b409d",
    "25753804e6a093c97b4eb5ee65cea00f47db728c",
    "522f4b495bc1818de3d077be76a69771d35a43b6",
    "6b3ce066a62dd6c4fabb83b5018bdfcf8a9456a5",
    "1beaf0afd05cb1a72e576525f15e7992b1e1d9dd",
    "4eb801241d4d2e460da0fed640175cf0f56ca720",
    "53ed7afeac5548d4b33f28f4f1c13a3b7707ac79",
    "0a2efc7732b00a38478d08ee1f90009cf4bca29d",
    "4f818a14c1744aa5a7e2c66de4669f602e4e1fdb",
    "6b8776f21750d872eadfa2f95d2ae796d9055c5e",
    "252e6fed0966e7209e6d16051c40f57781060d38",
    "59bef495783ad74799e44737b7967ace16b6be64",
    "3d132d15b30b522d7d3d3ed8544e6fdd9ab68a94",
    "5d51d4ffb2d8ea510cde17cb822b3d749cd08f4a",
    "1ecfd542e320a1b8f8b7cbcce2caa1e38621cd09",
    "46427a53f897c26dfed40d7ca8c91cd2479896fd",
    "1a6a5f5c4d57dc67f11fe2eca9770fa1838497ad",
    "12b2a865d1f6ef08ec6d9df186bc3fd8fa3adfea",
    "1aab9b7727d904829fce45df6ff9b453ce7eb5bd",
    "000b2384dc9485c9f4f9b99ec487d4f53556a562",
]

bls_pk_list = [
    "149342d0565f1645e40cd5aaaba7c6a29589d9346adb9c78e990b9f0d111dd3f48f23910fd96cf1d888fd9e841e8bc54934a572058158ed43edb4bb97c5672ef01", # genesis
    "3377255e474a9aa9caa13034d540200914970f98574538d5370d4958fc30a52c6cc2a41bf47b5828483c63e5d0b3d407ab4354c631fc0a57506df9a675d0c1c100",
    "4d07f24635343f83d99ec2c95a5596d0a830c040e55c9d4273a1bc891501d66ac0b3e1b2ac6639c32f279bdafb8f1f6ee4c71dcb07e066d00e4d3fb4524f066901",
    "20d392f9813d86534b8e9547a8f83902c1254ae82a5f59f1cffcaf57cf93fb43dacb03fe12863c9912b0321faadbb4f2d5e353dff4913d1f8b56390d16b94a1701",
    "4f53d674913b202d35b1e864adc35f133e457b78cf572ce3aee8fa95d296e52141e64c4cfc6895217bd63ffdc2263434cf72a89c54d5ca1f98bd1b45c6d671b300",
    "8a4e44c5240b45cec1665cbea836887fc96aa6eb5515a0e83f257aa593bb0721cd8b56af9d1f6a8b11bbff1f901186274771d3a7a40b23ae661aad247f1705b300",
    "770259cbef3e88bc4d1d153f6ae044078a29203f8f4132d3dd2667b192323d7a081e56d66c514f8fd041e0a3510c1d3a771dcbfdd24297cec723e809e5bc2b6901",
    "3a9c3a96914a71341343f81dc6639142c00ca35f7dfb8d6fd5a030b763328eb4787100dfb528c88b5992f8e13dc79ff9268448f1d7f7e6d0acd8877fa3d800ec01",
    "0b3513b1608673b2c6b1e4590e2a8a17e003f5858eba7ba88ccf79073b02bbe5e1c20d3a85cead36826c6d9df29c606ac535a3a30ef413aee240e98b2668c4e700",
    "38bc27a91fe38cf046242c78c2e7e0dbcc818be43cfdc9214dce685bd8a73564095ac1df167e1c816276ac8ae2b1bd0a9e0cae9e334eecd351a8bdb0d9e3c21200",
    "9b1d034183ecd06d55be9edefc6ba3103b348816caf7d1b9e8fd3ec02ce7abbf6003965639538d08fd1f8b98d47bb5f1f8c858b13b1d4653399e14ea423c375900",
    "55bd10775cd74ac612f351beb333d96a69168655bd7a5ebeec92abb43bc6a6ffa9f51f536e2222d7e3aa15a8957098ced0b8e408bd9bd425d93e519f55aa88cf01",
    "96dfe1441c9fffe6e4f803a96d8b1d4d3f7214b9af114be61c48251379fb9a11a3be627b7e91445ec00c4bca5f3f44c35acb34d51a956cca0126b17ffc2fca8801",
    "03d379430a109ceb5622f72bd2f1e3d9a617cfc2e609c116f88b30313a447837ad99ecec92a8e9c15b16ccc6a2e087b2e73423bb9cd1a8a19dc5a153d968e6f300",
    "218df49e7f0abf1e58584a3f914bf2632a6d6e7b13867462afafa7853448c2c70ccc11c7db366ea0be43d23069760e5c5b6653fbabdbaf00f14103891a3347fd00",
    "7b0adc4f6ec2e15b6f61c5b4f2eb626682770ac7a29327c4b567fcc7928e3e3c718916e806c89d1f26ba656ac4ad6b9282c9dfcd5fcec77d8998e07c5b3c09a200",
    "997501d2a4865188b67b2c691b5b40d76baf31ba5a3f91659017484931b3ebc57d3717bafd964d6067129958d240acbe9d01eefd6129ede0a11d9e9dde4db57a00",
    "826213df30ba1f2404d9a1dec9e2a7741d02efa1a7c823e05e48b14639b7f989ca180bb758a499088e05db7ba8b72113b38cecdbec4a91a05b98fe38f3d4cb6601",
    "2409d802f3e9badbbcd83c4b7060242e7e12866a5b610cfad4928312526b57c5aa5e3ab73b44851622e91cd1bd24af3c5683fa4d44bf83919ee2f012312793a600",
    "72aeed7cd99680a607f7515931457c97ed4da5230920116385ac2c6a2e6d6e3d6d1d86221fff9bf3a931951f619ade61097c26a9feef91b9a132d5015576f73301",
    "962872093876b9fe75cc23e01c3fb9e9a0c394e6a36ab8691b4c30a2ba1795a0bbdd125b1e382dc48c6fa7d5ab6161861a02d3622a1f88f16da32f91bfb20d5100",
    "8b5d5aaa7284b997e56427ce36b6cdb7eb30b5e3f19e1b2f8a017da793ea88ea62819e3a34aa91fb0cf3093d92c8b86d960d286045acbc74c78e26953e3d2d7401",
    "9662e5416a04c6751c4c27a7d56abd49c1f6478de3978335917304ff8c41986043840988a77d2956de24d1f8b71fc5c73ec775b9265421d98b8a5b403fe514bf01",
    "56ce202db5c52ddc42c2dad062c23ca3d7a86b0ec31390a9c607ea83c3cd0f83e56ba75e2c8a3d64b1cff6abffca6459f614c288200317dd8a3d0e6b943099e301",
    "0d0099f054d06d5ecb8337b0092068724fc76249f8f9c50b05da1149fd6f5824656c25c7dd919e815e5808dd8f8e791d378e9e7fa9fc1e7bb0f2dc0dfc52ba2f01",
    "846aede89f840207c7e63a71162780482a0d4a2505e4fffda525df20e6b93035e1a07980095a7d62c190caaf851f0eb68f217eb8232e767db3f36dd74cdd413801",
    "2439d8fc8b04b61da172b59dc25d41b52c35e77c7e45260fe3b557edfacc99cf428ef5e37d47bd8770567e55586ec9d77c9ec7739cc1fb138f41beb754f93f8b00",
    "67e645d3c1209629c8bf58615b5c498b4b57bb0cbfdd70777af16ea44ebcd2cac83d957982a184955f908eefa1469db4d4e159f054eff4174a5b6d6978d6be3101",
    "584367bab6c8c3c293eaa2e32182e59cafa16e24150270c433c6153e246556a296fb9bfe4093c9066eac5c9b309d134a10ebfc5a5b5ebc13e457edf4979c1bcf00",
    "4a8bfc28e2e8c73a2ce57dff0a86ef4cb850ae21033ed6b0d2ca1ac9dff7642fff56bac1ca14d70649be9ac0955d5ea66055c0d54fa40e32ddeeeb5fb205427d01",
    "a5bfe978b4e28e430216738cba13842ca95b128c10ba00a98c283f9a7e184b9c1d5c63904b41d8fb79ccce4a17f03d241b538bfe3fcc9c0afa9bbd79ebcc41d401",
    "93b10e3bd582ec235014e870dfb36074c3b74fee474839f0f5cced16614b08ffaec54d3071d6037bd99c571e999a961481b88cc9c3bf1f64a4ee52f0eda8ad3c00",
    "3f5d54633c0738fbcdc94426ddbc9c6f6db0c2574d31928eefbec43f02460c3f31673efd4e8a704cb54be3e497455bcd8f9ccd3922052cd786426286fa1c430800",
    "10f228910272e0459c599f4bfd8114f483983d6fad9eed0db494333feaae744c6f7c240e9851f78ab99c632c8db7fb94a3401cebf07be802c5979a6b76a9731001",
    "3226d4aeab8abab1368d61d34a3f16fcf500e2fa41613f77f947176c979965b26e17db2ca3827d1267edba5b267d952d292769403757c2008c5bed85be3dd89001",
    "36bd8651cbbcbab26edbee90de1b796c161cd6ad2ac71d09abb3a48f76da0363af5af4333259c1a0d87fc6f12751cd2074db2d98078d396caca247b995a47d5501",
    "33d072d5d12cacf3bb838bde33e69bb6a2a36d9d2e162f2c9ebc95436a7a5b7d8076dc3e4f2a2fd9719fb21d293476464d87c240517f84f90c04be039447cde701",
    "8dc2a213baaf3151c46a9b61435e0def398d2a6212b0ad212ab09718227b365727da0e15209877d6c7f96d01e1a9e099fb9479bc5bc92f6646bd29d47f81fe2a01",
    "01d103707e767d140616e7fa06305b21e2e120fd096a1d5bd00e4b05930dba65c4dfd3e1dd29c5ad83d607856236c6e9207c437fc66a6b6791ae74c5a6114e2001",
    "2cec23f95ac1651a487690a58500e986aec21b4104606862d7bdf7d14650a4cf05cbd1f6a36736981ee5a75b324e93a41382058c77a621f86d39e66e5c08760800",
    "5477f3859c9028811d4f934b9c6828a1d4ff6a42d91be0920bd55000dd62d28465538f5cb96ba7962c5478d3edfc5a9573ae209c2af56621137d5ea40fcacf9e01",
    "5c18f02a1a92628d89bc9c3e1bdec8b40706bf928582d41220323a933069f7536418c1df5b0d854517114f857a00c973e2191311d72f42ae5feef5dc0033a9f200",
    "178770e3f1291f7d4c740051a5f4d18700f30140871851f02349ddf3dac56c7eaaf42e1e223e7e014ef5b0b5649ce8985e5986756c9f84525f51552707bfc3c201",
    "368858e48e304f4225cc115ea0edcc7940d332170e60674edfa226762c4ef1441653259c28bef0ad3fb9cfa3f8371f9c77aec325a8e08e9ea73ebc9a6c1a044901",
    "5dbe50592e0f014a7eb5f7a06d6ec3cc87a117593fcce75b9f952fe9196012df2fe5161ec1008b9544b405bfe38f60d2647aa49284996174159494d1168ccb3900",
    "874e5ad14ede37c88a0570bfa9f599adb91da78d32fb57b279998e8fce3f76af8311b8a2477431e5a3c006f0faaff07c4540075b369d3b81aa96f67bbc6f906901",
    "8f639e8ece9aaec6fcbf3ec0421ca01785d4cec02dcba4f810ace7c9d26abe7819d6d04ca253596da931b8657e7433de35249c4ad2d3007fb579b99d5046db4700",
    "79c7286c34e128f3b65cf6b357f13d96607b56004ef03339cf253a162f26d2251896fe167ce06500cb045e818954ebfc0ac99b3bf2e7518100bd9b8b1152ab1400",
    "06065b88c8cfb6ebe2bf30d61e5c1ed70a0696061e0e7983e9d2bd8330019e8a2fbe910d601be60db22b4ee8a4dcebcd7090d333bd0e55cc51994b79d80eef2c01",
    "0a73648df76f2d31d587ebfc473872db1363ebfbf61931108b9eeb8ad96fbaf3de61d04f29d7aed4faa2696e66ffeb1246854bf04ef5ddda9711a0f1ecdb7e8901",
    "538484249849064fdc8c0ef62f9e84e08d90eba54aca3ff161c8568b764d963448deaa3cb9c59c954a8f17f5034d6ed03c0293d07e790d0b6a12ef83507c7e6801",
    "5a762b5b55e29495654604d4e77a3eba9aa844cd32b161f87234833ca82a98a884cf33f3c7d572424ebf00ebcf9bca11cdefc0dde0008d1b1fe17fbccbd45e9800",
    "92b59956b7ef15458e9a17507cba0d92bce4dadb8c837d34a0c803e26bb14b8243c4b3464c32631b725f97f0f61075dee3630530b35b2347549bedf95b32d33c01",
    "97e091c08160adf9d458333d395abfeba3589cd39eaae405fef1d1ed4f397778f92ee2088fbb84f8c06043d3b9c802393e02f70cd1be8e1c1fc820135e1ecedf01",
    "1897bd04f8354d473b12dd1ac6dfcee014f5151eed63febd55ca128d0e9a342fbf0b4606b2949c5ddff6796bd5d56cbc8e8f27584a0f818d96c482a66483f33c00",
    "5319c6f8b40a9f15e59132b508e5cbee1a2b50abc2af4b2de81a4960b268e9155292c4bba0e63fc9bb31c34e85e3d8fcf6cd2cd0d184e0f7e3244a0ea6fdd3ee01",
    "29b38db10fde287538bc8745a5547623eabfa33a5a778f4196ae9beeca9b995663f67ed5aff579fb553c2d376249f280e1d42dd0aea52e7cfeabdd1a7300f69201",
    "8459b5d0a75c73a674e14d2a69962cde095b27d3ba8250fbe051f48dd0ca45e7d9f854927c2e8af3c60d8f722a71438a7d2d6bffdf868fd99ce75ef452f555e201",
    "4f56c57527ac35a1f568292b355a3dbedb783e2961041a214f41dba56e54037a02cd4f611a287f951e3320df6e5c81d3d2232e761226d0ac65698216a1dfaf2001",
    "12de7561ae61261d2f7f625bbfb5ad95410021e8651d592a7d46d82bbeeb1c7e75cd16ddfa47cb7bb9867938877b6fce54a4ea8a6da9de5c2afca93e66893e1701",
    "2668870df5c43d54a47fdda27694c55349cb60d34d617a8d757db075f46335dced57878f94ed61aaa7a13e434ac9d1bb41f22481c4f4cf5e1e1599ed57e0ce9d01",
    "4e06b59b13a8ea86400c0fb4402a4af4764580fb309f19e6621605db0c43181f3c6ea3ec169036a0a408e6bf5bcc99928bab34bdea71d3730f56cc6d1a3d0e6b00",
    "6ea2b6d5b183eefdae19739ce09ea7c6258b23c2bc52f447ca91df1e52e569683fc7e8266c238af6d6e69fcdabd6f81b9ecd003b7731b7a89b1bdd83a48d8fd700",
    "57484473f630cfd73d0b02f0be471ca030c6599aac9c94664df079bdcaae71e34502ecf8c219ed146781d2a2eab4ef4cdaf8e07433859b4cb2073f0b6eeceab900",
    "8aff24ce31f769ecfffa3f664c585a4a524ba6554eca15a2afca46de7890f1f751a3af379658e40c24b1370ede54604f41cabb91310bbe50ae0d924800e3a20501",
    "15c6ddd28c9f2c03bc343af130ed717c6858333b7ff6597a7120e06207653184966eb48313611768e99427ae1c240a09284413b2ed78879c7ba10905324f839501",
    "1195a6bf564a0589d72816321846a50d04118239ff9fdebbca699d242974b5c7d0b74f16110fc0663a9638db8f83f0d2f9bba278a73ada543abacd4a1d0b2b4e00",
    "3921539207251aa2dda2d4613a3258af868782db9e5f4279cbd1c8cfbe0680e27c49b822f40c1ea559e7d3956c2f302cc92ceeb54513e0454cb38a1113eb0be101",
    "11e4c401e6adc3195a8ae0db00e79bc076c279906e174cee8aa429c7720fcfae5c97255c538ba14e0d88d6a20ae9c61a1ef152b0c63170f87e87badda3811c8b00",
    "62138ee440152592166c640c6c4d396d1bc24dda17a66904807f4c7611b34b36ab88e4622bf26d593d64915d942154e2ff79f03894ed3d5f6adb53cffdf995d601",
    "0dad90f633c943389c682f6a276e733b384a7c82689e35ea042604f6f7ce15b845ba4bf42a7ad40eeafa72e6a0a2db9fe5d57fd316cef4f14eae03659cc4a54e01",
    "79e12a27f56b08c732376f924513659d711cc61126fdd243f92d61af2a2a8e2c3a9acf4ab0137fe3ba8f98b5fe838a407f103029b3f33a6a338468911459e6f200",
    "4983253ea50ba3aabc56844796c6c4f054d262da845f150d60336dcc94b58c2e793077badc1b730764865354d5759ec17ec23e9c6fe43906d1cd915db54447d601",
    "0018c0f59ba7d33bb628019034fb5a862dd66a274ab61a3b6911525ea347fa838dba8e3eaa760d1f47f1c5c82e68c37fcbccadb30f66458c6b048788d2df6e4b01",
    "197da0cf8752d2088a5e1ddf6f15479a818fd16c1fd26737a0cd098bc5683fb5d83a4246c78187a296b00895953200163483e3cf69cde0fd1298b29841f8f1da01",
    "85233a92cbc3235f5cce51747a0f1a57dd38968ee347399d9aaefaecebff32a40c1329670bfe60087d375b508383b429965ae8b3cb4ac6a0fb41aa46f4eee11401",
    "73b45b9e143b766dafffa0496d7157744ec0bc76999c450936ecf97e54bef79717b4bea05927151e8560f8b2dd2aca811d5c4f1d9c982c1fbb01f22fd2d4077601",
    "1b9b23a9a8a270d2d9eddc6bbaa99147707026b12a0817b2acee7df7992e3c361055f061dc2d711a65d8f1d173577c37ebcf5a40e4b4b283afae13b193a9e09501",
    "1bc78ec092a4d5b80289d6a8c1f7b68d4e31a6e0ad63ad8143041bf393acd0cd516d77ee19f1ce348e6a92246582ef5a8443dba508caa33dbbe546c782c7746301",
    "a26d4aded848c50cd47e325f12358d92f2a09c9d7461b2a34bf499fc9d49a55aadeadc205b7cb6825acae2c52fc8917702b43e74b84083a62ecb73a4ed4c621501",
    "43a01c4f75f04d00119b17fc8484e8eb5674c88a0641f2249055f0da233849684e98b744a24abc9a09e662c8d4c9612ad07844e9c5ebe86bc2a6ce75e8d02a2901",
    "5541d90298ae009c12c8c5029fea34f80a13f5bc46173c2f6f0e29069ec2d6504d85e1ca5b2fd8428b10733c95620326170386a2115bc82dd00354c9de683ed101",
    "3f47a7825d45886cab9fc3e7205c8b461cc2e28343f4643c4e912ae73a3a68f74e67a41ab5a38fc7dca96b28f765ac508ce54354b926ff3792728050f5dd3b4000",
    "17e7358cd3047551d3f979ff1b29180abbaae6c8b375d5d5673760e053648b38386036f35fcc45070d1097fdf3582e59290b760c7c8e9cb420010cc0d256265b00",
    "4eec30d5863ca4392273ea9d2949a74a4735a13304f4199dd2bece12d31f301b0382c304cf4137b4a96283d7b9c6c1a105ffba52d01b9e66d42dbbe9aa9e145f00",
    "5003bf4a47a2534178e73af4c098f36717f3ee8a6494c653c18f5b75d0e36076f93abdad1630929d95c092407bb27fe9d589e91803b07822c1c3a4163c53082701",
    "0e761ba68b537c860e9741970b7805e5fca3ef800389ed04c9eb5c448c619be0ed9f57c34124ed8373ed0f4534bdc6e5f4ffb586979fa12b38a2ac3155940dba00",
    "48a3dda59e302561ce14ff86333a22815b04c0de9711f5c582783cf301a0f0f9df937132cfffeb975427c4511c0a85b146a1cf13bbdedd2015527d7bfd57006901",
    "36d23e4f73ba462d250349fc7b5d7de0e5fc2431b7cf2699f5022ccffd7833beac49cdf110ed82b6caaed1b612533bde693110a294f4c4fda4adf290a9507a0b01",
    "9c44a96c370415f886dde6c970edade6fceca86d534ba14543d108c35469db7f2a58fd3b345b5f313e9c22ebfe61131bc4cdba7151e968651f4614ac8165de5f01",
    "67f98de953a2276b4d27bfc5b8065b8815eb904411f2102456dab6d51311e74240c6e06c78e73dded88d48753388052b00370c69c8c14e52641f3b609e46966d00",
    "33a7d0d2678624c2c3a2e03bcd148a8806d944c11e5b27112e564de730a976c81bfcafe1e99e8d64c39e9f11cf680842169163d1eedef27fc855bd8155df3fe801",
    "8f157514ac9d25ab23b654ced647f0defaa2a61c9df3eb3769e5dec4bf144773a58b498a4093794ca17e59beded2a495dab2fe0be396ed5475f8783379ff77fc01",
    "7bff250a500542e2beb0b80bc7acbf6baabd63bc4e19cf00843c6acfe94b689999bfed1c77920e464da74fa8e5539528c720f13c02c3cbe6cf9acc932feddf6c01",
    "725435733f2dff9f164cb75e5034c6f765fd98427989381987aadbf0c000bf8c65ac80a80039173767765ea241730f9bfd290a1924d3019e1c0b34b54cccd3aa00",
    "4136a622c5b874005c5de93a19da59a13e7c7d7744ffc438fa3fd5f22d9b688d3585d0d1d369ad3d12d669888aafa00b4eff80b86e5bcc93234ba5c5bce0a7db01",
    "2dafce9daa153e65216d8657a674e85cdd4e1eec7646af8c4401e01260afeb72edec58098a5eb16a740054dbda4214b0b4b859411a476a0451350b3e9ed2742500",
    "39c8c1079dca068779c5745d43177cdcf106a1cd7549241e52e69c4009d0f0f582be0651f795cfdedf260194aaf9d02406788a57f286e3ace1b4827e030628ce01",
    "9cb958b673ad3c08b8dc70438f5e3ee7e1b2766e866f89129c42fe69ff2dee974554fdc3d0b7d45ceef91b1bfbb4f6cac5eeefc4cc8e1ebfd1ce6050a938185600",
    "1ee7e68f6e1d27b053b3d3618dfe4cb72bd1ce2925844dda08c80259e74ea465d084c4230e4e36532be7d279c8ef8507a29e38176a40c8935fdf8a5a2b816b3800",
    "8f34633f3ced31e241311cf81e9920ea7fea8a29093debfb4bda6f8889504f2c004e1687b54835f13ad458941a734d4a82235808632f9b7706eca47616c4c62d00",
    "48f2d7d63e5f2e17fde6131bcfd94dbd09c4d2b1b88e9dace20028542b21a4942fc93a708bd1aeab90bc538dde5d4447148583bf0f34f269628c3abe56f78df300",
    "965b09d52de7ad8c44adff4b9a854a77455f8e4f72862b686aeb7f9560993389b43a50245edceca2aadfa7a7af6445e14684c2dbb2cea6ecc0f8795b79fe79e401",
]

def generate_keypair():
    with open('keypair.txt') as f:
       elements = f.read().splitlines()
    allMinerPris = elements[0::6]
    allMinerPubs = elements[1::6]
    allPriKeys = elements[2::6]
    allPubKeys = elements[3::6]
    allAccounts = elements[4::6]  
    nullvalue = elements[5::6]
    # for i in range(0,len(allMinerPris)):
    #     print(allMinerPris[i])
    # for i in range(0,len(allMinerPubs)):
    #     print(allMinerPubs[i])
    # for i in range(0,len(allAccounts)):
    #     print(allAccounts[i])
    # for i in range(0,len(allPriKeys)):
    #     print(allPriKeys[i])
    # for i in range(0,len(allPubKeys)):
    #     print(allPubKeys[i])
    print("allMinerPris length:",len(allMinerPris))
    print("allMinerPubs length:",len(allMinerPubs))
    print("allPriKeys length:",len(allPriKeys))
    print("allPubKeys length:",len(allPubKeys))
    print("blsPriKeys length:",len(bls_sk_list))
    print("blsPubKeys length:",len(bls_pk_list))
    print("allAccounts length:",len(allAccounts))
    content = ""
    for i in range(0,len(allMinerPris)):
         content=content+  allMinerPris[i] +"\n"\
                        + allMinerPubs[i] +"\n"\
                        + allPriKeys[i] +"\n"\
                        + allPubKeys[i] +"\n"\
                        + "bls_sk:"+bls_sk_list[i+1] +"\n"\
                        + "bls_pk:"+bls_pk_list[i+1] +"\n"\
                        + allAccounts[i] +"\n"+"\n"
    
    writefile("newfile.txt",content)

def readfile(fname):
	fileold = open(fname, "r")
	content = fileold.readlines()
	fileold.close()
	return content

def writefile(fname,content):
	filenew = open(fname, "w")
	filenew.writelines(content)
	filenew.close()

generate_keypair()

