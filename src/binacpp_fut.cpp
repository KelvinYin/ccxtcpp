/*
	Date  : 2023/07/15
	C++ library for Binance Futures API.
*/
#include <cpr/cpr.h>

#include "binacpp_fut.h"
#include "binacpp_logger.h"
#include "binacpp_utils.h"

void BinaFuturesCPP::init(string &key, string &secret)
{
	api_key = key;
	secret_key = secret;
}

void BinaFuturesCPP::cleanup()
{
}

//------------------
// GET /fapi/v1/time
//------------
void BinaFuturesCPP::get_serverTime(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_serverTime>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/time";

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_serverTime> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_serverTime> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_serverTime> Failed to get anything.");
	}
}

//------------------
// GET /fapi/v1/exchangeInfo
//------------------
void BinaFuturesCPP::get_exchangeInfo(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_exchangeInfo>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/exchangeInfo";

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_exchangeInfo> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_exchangeInfo> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_exchangeInfo> Failed to get anything.");
	}
}

//--------------------
// Get Market Depth
//
// GET /fapi/v1/depth
//
// Name		Type		Mandatory	Description
// symbol	STRING		YES
// limit	INT			NO			Default 500; Valid limits:[5, 10, 20, 50, 100, 500, 1000]

void BinaFuturesCPP::get_depth(const char *symbol, int limit, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_depth>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/depth?";

	string querystring("symbol=");
	querystring.append(symbol);
	querystring.append("&limit=");
	querystring.append(to_string(limit));
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_depth> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_depth> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_depth> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_depth> Failed to get anything.");
	}
}

//--------------------
// Get recent market trades
//
// GET /fapi/v1/trades
//
// Name		Type		Mandatory	Description
// symbol	STRING		YES
// limit	INT			NO			Default 500; Max:1000

void BinaFuturesCPP::get_trades(const char *symbol, int limit, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_trades>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/trades?";

	string querystring("symbol=");
	querystring.append(symbol);
	querystring.append("&limit=");
	querystring.append(to_string(limit));
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_trades> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_trades> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_trades> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_trades> Failed to get anything.");
	}
}

//--------------------
// Get Aggregated Trades list
/*

GET /fapi/v1/aggTrades

Name		Type	Mandatory	Description
symbol		STRING	YES
fromId		LONG	NO		ID to get aggregate trades from INCLUSIVE.
startTime	LONG	NO		Timestamp in ms to get aggregate trades from INCLUSIVE.
endTime		LONG	NO		Timestamp in ms to get aggregate trades until INCLUSIVE.
limit		INT		NO		Default 500; max 500.
*/

void BinaFuturesCPP::get_aggTrades(
	const char *symbol,
	int fromId,
	time_t startTime,
	time_t endTime,
	int limit,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_aggTrades>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/aggTrades?";

	string querystring("symbol=");
	querystring.append(symbol);

	if (startTime != 0 && endTime != 0)
	{
		querystring.append("&startTime=");
		querystring.append(to_string(startTime));

		querystring.append("&endTime=");
		querystring.append(to_string(endTime));
	}
	else
	{
		querystring.append("&fromId=");
		querystring.append(to_string(fromId));

		querystring.append("&limit=");
		querystring.append(to_string(limit));
	}
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_aggTrades> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_aggTrades> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_aggTrades> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_aggTrades> Failed to get anything.");
	}
}

//-----------------
/*
Get KLines( Candle stick / OHLC )
GET /fapi/v1/klines

Name		Type	Mandatory	Description
symbol		STRING	YES
interval	ENUM	YES
limit		INT		NO			Default 500; max 500.
startTime	LONG	NO
endTime		LONG	NO
*/
void BinaFuturesCPP::get_klines(
	const char *symbol,
	const char *interval,
	int limit,
	time_t startTime,
	time_t endTime,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_klines>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/klines?";

	string querystring("symbol=");
	querystring.append(symbol);

	querystring.append("&interval=");
	querystring.append(interval);

	if (startTime > 0 && endTime > 0)
	{
		querystring.append("&startTime=");
		querystring.append(to_string(startTime));

		querystring.append("&endTime=");
		querystring.append(to_string(endTime));
	}
	else if (limit > 0)
	{
		querystring.append("&limit=");
		querystring.append(to_string(limit));
	}

	url.append(querystring);
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_klines> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_klines> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_klines> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_klines> Failed to get anything.");
	}
}

//--------------------
// Get 24hr ticker price change statistics
//
// Name		Type	Mandatory	Description
// symbol	STRING	YES
//
void BinaFuturesCPP::get_24hr(const char *symbol, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_24hr>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/ticker/24hr?";

	string querystring("symbol=");
	querystring.append(symbol);

	url.append(querystring);
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_24hr> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_24hr> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_24hr> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_24hr> Failed to get anything.");
	}
}

//----------
// Get Single Pair's Price
// GET /fapi/v1/ticker/price
//
// Name		Type	Mandatory	Description
// symbol	STRING	NO
//
void BinaFuturesCPP::get_price(const char *symbol, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_price>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/ticker/price?";

	string querystring;
	if (symbol != nullptr && strlen(symbol) > 0)
	{
		querystring.append("symbol=");
		querystring.append(symbol);
	}
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_price> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_price> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_price> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_price> Failed to get anything.");
	}
}

//--------------
// Best price/qty on the order book for a symbol or symbols.
// GET /fapi/v1/ticker/bookTicker
//
//	Name	Type	Mandatory	Description
//	symbol	STRING	NO
//
void BinaFuturesCPP::get_bookTicker(const char *symbol, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_BookTicker>");

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/ticker/bookTicker?";

	string querystring;
	if (symbol != nullptr && strlen(symbol) > 0)
	{
		querystring.append("symbol=");
		querystring.append(symbol);
	}
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_BookTicker> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_BookTicker> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_BookTicker> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_BookTicker> Failed to get anything.");
	}
}

//--------------------
// Get current account information. (SIGNED)
//
// GET /fapi/v2/balance
//
// 	Name		Type	Mandatory	Description
//	recvWindow	LONG	NO
//	timestamp	LONG	YES
//
void BinaFuturesCPP::get_balance(long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v2/balance?";
	string querystring("timestamp=");
	querystring.append(to_string(get_current_ms_epoch()));

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=");
		querystring.append(to_string(recvWindow));
	}

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=");
	querystring.append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance> Done.");
	}
	else
	{
		// std::cout << r.status_code << ":" << r.text << std::endl;
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_balance> Failed to get anything.");
	}
}

//--------------------
// Get current account information. (SIGNED)
//
// GET /fapi/v2/account
//
// 	Name		Type	Mandatory	Description
//	recvWindow	LONG	NO
//	timestamp	LONG	YES
//
void BinaFuturesCPP::get_account(long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_account>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_account> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v2/account?";
	string querystring("timestamp=");
	querystring.append(to_string(get_current_ms_epoch()));

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=");
		querystring.append(to_string(recvWindow));
	}

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=");
	querystring.append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_account> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_account> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_account> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_account> Failed to get anything.");
	}
}

void BinaFuturesCPP::send_order(
	const char *symbol,
	const char *side,
	const char *type,
	const char *timeInForce,
	const char *reduceOnly,
	double quantity,
	double price,
	const char *newClientOrderId,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::send_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::send_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	// url += "/fapi/v1/order?";
	url += "/fapi/v1/order?";

	string post_data("symbol=");
	post_data.append(symbol);
	post_data.append("&side=").append(side);
	post_data.append("&type=").append(type);
	if (strcmp(type, "MARKET") != 0) // type != MARKET
	{
		if (timeInForce != nullptr && strlen(timeInForce) > 0)
			post_data.append("&timeInForce=").append(timeInForce);

		post_data.append("&price=").append(to_string(price));
	}
	post_data.append("&quantity=").append(to_string(quantity));
	if (reduceOnly != nullptr && strlen(reduceOnly) > 0)
	{
		post_data.append("&reduceOnly=").append(reduceOnly);
	}
	if (newClientOrderId != nullptr && strlen(newClientOrderId) > 0)
	{
		post_data.append("&newClientOrderId=").append(newClientOrderId);
	}
	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=").append(to_string(recvWindow));
	}
	post_data.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=").append(signature);

	BinaCPP_logger::write_log("<BinaFuturesCPP::send_order> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Post(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::send_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::send_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::send_order> Failed to get anything.");
	}
}

void BinaFuturesCPP::send_marketOrder(
	const char *symbol,
	const char *side,
	const char *reduceOnly,
	double quantity,
	const char *newClientOrderId,
	long recvWindow,
	Json::Value &json_result)
{
	send_order(symbol, side, "MARKET", nullptr, reduceOnly, quantity, 0.0, newClientOrderId, recvWindow, json_result);
}

//------------
// cancel order (SIGNED)
// DELETE /fapi/v1/order
//
// symbol				STRING	YES
// symbol				STRING	YES
// orderId				LONG	NO
// origClientOrderId	STRING	NO
// recvWindow			LONG	NO
// timestamp			LONG	YES
//

void BinaFuturesCPP::cancel_order(const char *symbol, long orderId, const char *origClientOrderId, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/order?";

	string post_data("symbol=");
	post_data.append(symbol);

	if (orderId > 0)
	{
		post_data.append("&orderId=").append(to_string(orderId));
	}

	if (strlen(origClientOrderId) > 0)
	{
		post_data.append("&origClientOrderId=").append(origClientOrderId);
	}

	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=").append(to_string(recvWindow));
	}

	post_data.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=").append(signature);

	BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Delete(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_order> Failed to get anything.");
	}
}

//--------------------
// Cancel All Open Orders
// DELETE /fapi/v1/allOpenOrders
// Name			Type	Mandatory	Description
// symbol		STRING	YES
// recvWindow	LONG	NO
// timestamp	LONG	YES
//
void BinaFuturesCPP::cancel_allOrder(const char *symbol, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/allOpenOrders?";

	string post_data("symbol=");
	post_data.append(symbol);

	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=").append(to_string(recvWindow));
	}

	post_data.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=").append(signature);

	BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Delete(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::cancel_allOrder> Failed to get anything.");
	}
}

//--------------------
// Get trades for a specific account and symbol. (SIGNED)
/*
GET /fapi/v3/myTrades
Name		Type	Mandatory	Description
symbol		STRING	YES
limit		INT		NO	Default 500; max 500.
fromId		LONG	NO	TradeId to fetch from. Default gets most recent trades.
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaFuturesCPP::get_myTrades(
	const char *symbol,
	int limit,
	long fromId,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v3/myTrades?";

	string querystring("symbol=");
	querystring.append(symbol);

	if (limit > 0)
	{
		querystring.append("&limit=");
		querystring.append(to_string(limit));
	}

	if (fromId > 0)
	{
		querystring.append("&fromId=");
		querystring.append(to_string(fromId));
	}

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=");
		querystring.append(to_string(recvWindow));
	}

	querystring.append("&timestamp=");
	querystring.append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=");
	querystring.append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_myTrades> Failed to get anything.");
	}
}

//--------------------
// Get all open orders on a symbol.
//
// GET /fapi/v1/openOrders
//
// 	Name		Type	Mandatory	Description
//	symbol		STRING	NO
//  recvWindow	LONG	NO
//  timestamp	LONG	YES
//
void BinaFuturesCPP::get_openOrders(const char *symbol, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/openOrders?";

	if (symbol == nullptr)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> symbol is empty.");
		return;
	}

	string querystring("symbol=");
	querystring.append(symbol);

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=").append(to_string(recvWindow));
	}
	querystring.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=").append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> Failed to get anything.");
	}
}

void BinaFuturesCPP::get_openOrder(const char *symbol, long orderId, const char *origClientOrderId, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrders> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/openOrder?";

	if (symbol == nullptr)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder> symbol is empty.");
		return;
	}

	string querystring("symbol=");
	querystring.append(symbol);

	if (orderId > 0)
	{
		querystring.append("&orderId=").append(to_string(orderId));
	}

	if (strlen(origClientOrderId))
	{
		querystring.append("origClientOrderId").append(origClientOrderId);
	}

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=").append(to_string(recvWindow));
	}
	querystring.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=").append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_openOrder> Failed to get anything.");
	}
}

//--------------------
// Get all account orders; active, canceled, or filled.
//
// GET /fapi/v1/allOrders
//
// Name			Type	Mandatory	Description
// symbol		STRING	YES
// orderId		LONG	NO
// limit		INT		NO		Default 500; max 500.
// recvWindow	LONG	NO
// timestamp	LONG	YES
//
void BinaFuturesCPP::get_allOrders(const char *symbol, long orderId, long startTime, long endTime,
	int limit, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/allOrders?";

	string querystring("symbol=");
	querystring.append(symbol);

	if (orderId > 0)
	{
		querystring.append("&orderId=").append(to_string(orderId));
	}

	if (startTime > 0)
	{
		querystring.append("&startTime=").append(to_string(startTime));
	}

	if (endTime > 0)
	{
		querystring.append("&endTime=").append(to_string(endTime));
	}

	if (limit > 0)
	{
		querystring.append("&limit=").append(to_string(limit));
	}

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=").append(to_string(recvWindow));
	}

	querystring.append("&timestamp=").append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=").append(signature);
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_allOrders> Failed to get anything.");
	}
}

//------------------
/*
// get order (SIGNED)
GET /fapi/v1/order

Name				Type	Mandatory	Description
symbol				STRING	YES
orderId				LONG	NO
origClientOrderId	STRING	NO
recvWindow			LONG	NO
timestamp			LONG	YES
*/

void BinaFuturesCPP::get_order(const char *symbol, long orderId, const char *origClientOrderId, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::get_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/order?";
	string action = "GET";

	string querystring("symbol=");
	querystring.append(symbol);

	if (orderId > 0)
	{
		querystring.append("&orderId=");
		querystring.append(to_string(orderId));
	}

	if (strlen(origClientOrderId) > 0)
	{
		querystring.append("&origClientOrderId=");
		querystring.append(origClientOrderId);
	}

	if (recvWindow > 0)
	{
		querystring.append("&recvWindow=");
		querystring.append(to_string(recvWindow));
	}

	querystring.append("&timestamp=");
	querystring.append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
	querystring.append("&signature=");
	querystring.append(signature);

	url.append(querystring);

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> url = |%s|", url.c_str());

	cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> Failed to get anything.");
	}

	BinaCPP_logger::write_log("<BinaFuturesCPP::get_order> Done.\n");
}

//--------------------
// Start user data stream (API-KEY)

void BinaFuturesCPP::start_userDataStream(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/userDataStream";

	BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream> url = |%s|", url.c_str());

	cpr::Response r = cpr::Post(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		try
		{
			Json::Reader reader;
			json_result.clear();
			reader.parse(r.text, json_result);
		}
		catch (exception &e)
		{
			BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::start_userDataStream> Failed to get anything.");
	}
}

//--------------------
// Keepalive user data stream (API-KEY)
void BinaFuturesCPP::keep_userDataStream(const char *listenKey)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::keep_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::keep_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/userDataStream";

	string post_data("listenKey=");
	post_data.append(listenKey);

	BinaCPP_logger::write_log("<BinaFuturesCPP::keep_userDataStream> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Put(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::keep_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::keep_userDataStream> Failed to get anything.");
	}
}

//--------------------
// Keepalive user data stream (API-KEY)
void BinaFuturesCPP::close_userDataStream(const char *listenKey)
{
	BinaCPP_logger::write_log("<BinaFuturesCPP::close_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::close_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_FUTURE_HOST);
	url += "/fapi/v1/userDataStream";

	string post_data("listenKey=");
	post_data.append(listenKey);

	BinaCPP_logger::write_log("<BinaFuturesCPP::close_userDataStream> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Delete(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::close_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaFuturesCPP::close_userDataStream> Failed to get anything.");
	}
}
