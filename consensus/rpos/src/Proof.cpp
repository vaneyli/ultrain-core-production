#include "rpos/Proof.h"

#include <cstdint>
#include <limits>

#include <crypto/Ed25519.h>
#include <rpos/Utils.h>

namespace ultrainio {
    Proof::Proof(const Signature& signature) : m_sign(signature) {}

    Proof::Proof(const std::string& hexString) : m_sign(hexString) {}

    Proof::operator std::string() const {
        return std::string(m_sign);
    }

    double Proof::getRand() const {
        uint32_t priority = getPriority();
        return static_cast<double>(priority) / std::numeric_limits<uint32_t>::max();
    }

    uint32_t Proof::getPriority() const {
        if (!isValid()) {
            return std::numeric_limits<uint32_t>::max();
        }
        uint8_t raw[Ed25519::SIGNATURE_LEN];
        if (!m_sign.getRaw(raw, Ed25519::SIGNATURE_LEN)) {
            return std::numeric_limits<uint32_t>::max();
        }

        // get a 32-bit uint32_t number, get 192 - 224 bit
        return Utils::toInt(raw, Ed25519::SIGNATURE_LEN, 24);
    }

    bool Proof::isValid() const {
        return m_sign.isValid();
    }

    Signature Proof::getSignature() const {
        return m_sign;
    }
}