/*
 * Copyright 2017 Sony Corporation
 */

#include "Poco/Net/SSLException.h"

#include "easyhttpcpp/common/CoreLogger.h"
#include "easyhttpcpp/common/StringUtil.h"
#include "easyhttpcpp/HttpException.h"

#include "SslContextCreatorImpl.h"

using easyhttpcpp::common::StringUtil;

namespace easyhttpcpp {

static const std::string Tag = "SslContextCreatorImpl";

Poco::Net::Context::Ptr SslContextCreatorImpl::createContext(EasyHttpContext::Ptr pContext)
{
    const std::string& rootCaDirectory = pContext->getRootCaDirectory();
    const std::string& rootCaFile = pContext->getRootCaFile();

    // TODO: find a way to use the configured certificates
    // always use Windows default certificate store.
    try {
        // Windows default Certificate Store
        Poco::Net::Context::Ptr pPocoContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "",
            Poco::Net::Context::VERIFY_RELAXED, Poco::Net::Context::OPT_TRUST_ROOTS_WIN_CERT_STORE);
        return pPocoContext;
    } catch (const Poco::Exception& e) {
        EASYHTTPCPP_LOG_D(Tag, "createPocoContext: Poco::Exception occurred. message=[%s]", e.message().c_str());
        throw HttpExecutionException(StringUtil::format("sendRequest initialization error occurred. message=[%s]",
            e.message().c_str()), e);
    }
}

} /* namespace easyhttpcpp */
