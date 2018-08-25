#pragma once

#include <string>

#include <crypto/Digest.h>
#include <crypto/PublicKey.h>
#include <crypto/Signature.h>

namespace ultrainio {
    // ed25519
    class PrivateKey {
    public:
        static PrivateKey generate();

        PrivateKey() = default;
        // hex string
        explicit PrivateKey(const std::string& key, const PublicKey& publicKey = PublicKey());

        PrivateKey(uint8_t* rawKey, size_t len, const PublicKey& publicKey = PublicKey());

        PrivateKey(const PrivateKey& rhs) = default;

        PrivateKey&operator = (const PrivateKey& rhs) = default;

        explicit operator std::string() const;

        Signature sign(const Digest& digest) const;

        // valid when PrivateKey produced by PrivateKey::generate now
        PublicKey getPublicKey() const;

        bool isValid() const;

    private:
        bool getRaw(uint8_t* rawKey, size_t len) const;

        std::string m_key;
        PublicKey m_publicKey;
        // (qinxiaofen)this may be remove after remove UranusController::
        friend class UranusNode;
    };
}