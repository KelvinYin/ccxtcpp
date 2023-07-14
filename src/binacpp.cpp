/*
	Author: tensaix2j
	Date  : 2017/10/15

	C++ library for Binance API.
*/
#include <cpr/cpr.h>

#include "binacpp.h"
#include "binacpp_logger.h"
#include "binacpp_utils.h"

void BinaCPP::init(string &key, string &secret)
{
	api_key = key;
	secret_key = secret;
}

void BinaCPP::cleanup()
{
}

//------------------
// GET api/v1/exchangeInfo
//------------------
void BinaCPP::get_exchangeInfo(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_exchangeInfo>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/exchangeInfo";

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
			BinaCPP_logger::write_log("<BinaCPP::get_exchangeInfo> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_exchangeInfo> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_exchangeInfo> Failed to get anything.");
	}
}

//------------------
// GET /api/v1/time
//------------
void BinaCPP::get_serverTime(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_serverTime>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/time";

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
			BinaCPP_logger::write_log("<BinaCPP::get_serverTime> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_serverTime> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_serverTime> Failed to get anything.");
	}
}

//--------------------
// Get Latest price for all symbols.
// GET /api/v1/ticker/allPrices

void BinaCPP::get_allPrices(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_allPrices>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/ticker/allPrices";

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
			BinaCPP_logger::write_log("<BinaCPP::get_allPrices> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_allPrices> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_allPrices> Failed to get anything.");
	}
}

//----------
// Get Single Pair's Price
double BinaCPP::get_price(const char *symbol)
{
	BinaCPP_logger::write_log("<BinaCPP::get_price>");

	double ret = 0.0;
	Json::Value alltickers;
	string str_symbol = string_toupper(symbol);
	get_allPrices(alltickers);

	for (int i = 0; i < alltickers.size(); i++)
	{
		if (alltickers[i]["symbol"].asString() == str_symbol)
		{
			ret = atof(alltickers[i]["price"].asString().c_str());
			break;
		}
	}
	return ret;
}

//--------------------
// Get Best price/qty on the order book for all symbols.
// GET /api/v1/ticker/allBookTickers

void BinaCPP::get_allBookTickers(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_allBookTickers>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/ticker/allBookTickers";

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
			BinaCPP_logger::write_log("<BinaCPP::get_allBookTickers> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_allBookTickers> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_allBookTickers> Failed to get anything.");
	}
}

//--------------
void BinaCPP::get_bookTicker(const char *symbol, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_BookTickers>");

	Json::Value alltickers;
	string str_symbol = string_toupper(symbol);
	get_allBookTickers(alltickers);

	for (int i = 0; i < alltickers.size(); i++)
	{
		if (alltickers[i]["symbol"].asString() == str_symbol)
		{
			json_result = alltickers[i];
			break;
		}
	}
}

//--------------------
// Get Market Depth
//
// GET /api/v1/depth
//
// Name	Type		Mandatory	Description
// symbol	STRING		YES
// limit	INT		NO		Default 100; max 100.

void BinaCPP::get_depth(const char *symbol, int limit, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_depth>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/depth?";

	string querystring("symbol=");
	querystring.append(symbol);
	querystring.append("&limit=");
	querystring.append(to_string(limit));
	url.append(querystring);

	BinaCPP_logger::write_log("<BinaCPP::get_depth> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_depth> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_depth> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_depth> Failed to get anything.");
	}
}

//--------------------
// Get Aggregated Trades list
/*

GET /api/v1/aggTrades

Name		Type	Mandatory	Description
symbol		STRING	YES
fromId		LONG	NO		ID to get aggregate trades from INCLUSIVE.
startTime	LONG	NO		Timestamp in ms to get aggregate trades from INCLUSIVE.
endTime		LONG	NO		Timestamp in ms to get aggregate trades until INCLUSIVE.
limit		INT		NO		Default 500; max 500.
*/

void BinaCPP::get_aggTrades(
	const char *symbol,
	int fromId,
	time_t startTime,
	time_t endTime,
	int limit,
	Json::Value &json_result)
{

	BinaCPP_logger::write_log("<BinaCPP::get_aggTrades>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/aggTrades?";

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

	BinaCPP_logger::write_log("<BinaCPP::get_aggTrades> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_aggTrades> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_aggTrades> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_aggTrades> Failed to get anything.");
	}
}

//--------------------
// Get 24hr ticker price change statistics
/*
Name	Type	Mandatory	Description
symbol	STRING	YES
*/
void BinaCPP::get_24hr(const char *symbol, Json::Value &json_result)
{

	BinaCPP_logger::write_log("<BinaCPP::get_24hr>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/ticker/24hr?";

	string querystring("symbol=");
	querystring.append(symbol);

	url.append(querystring);
	BinaCPP_logger::write_log("<BinaCPP::get_24hr> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_24hr> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_24hr> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_24hr> Failed to get anything.");
	}
}

//-----------------
/*
Get KLines( Candle stick / OHLC )
GET /api/v1/klines

Name		Type	Mandatory	Description
symbol		STRING	YES
interval	ENUM	YES
limit		INT		NO	Default 500; max 500.
startTime	LONG	NO
endTime		LONG	NO
*/

void BinaCPP::get_klines(
	const char *symbol,
	const char *interval,
	int limit,
	time_t startTime,
	time_t endTime,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_klines>");

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/klines?";

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
	BinaCPP_logger::write_log("<BinaCPP::get_klines> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_klines> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_klines> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_klines> Failed to get anything.");
	}
}

//--------------------
// Get current account information. (SIGNED)
/*
GET /api/v3/account

Parameters:
Name		Type	Mandatory	Description
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaCPP::get_account(long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_account>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_account> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/account?";
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

	BinaCPP_logger::write_log("<BinaCPP::get_account> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_account> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_account> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_account> Failed to get anything.");
	}
}

//--------------------
// Get trades for a specific account and symbol. (SIGNED)
/*
GET /api/v3/myTrades
Name		Type	Mandatory	Description
symbol		STRING	YES
limit		INT		NO	Default 500; max 500.
fromId		LONG	NO	TradeId to fetch from. Default gets most recent trades.
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaCPP::get_myTrades(
	const char *symbol,
	int limit,
	long fromId,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_myTrades>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_myTrades> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/myTrades?";

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

	BinaCPP_logger::write_log("<BinaCPP::get_myTrades> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_myTrades> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_myTrades> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_myTrades> Failed to get anything.");
	}
}

//--------------------
// Open Orders (SIGNED)
/*
GET /api/v3/openOrders

Name		Type	Mandatory	Description
symbol		STRING	YES
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaCPP::get_openOrders(const char *symbol, long recvWindow, Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_openOrders>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_openOrders> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/openOrders?";

	string querystring("symbol=");
	querystring.append(symbol);

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

	BinaCPP_logger::write_log("<BinaCPP::get_openOrders> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Failed to get anything.");
	}
}

//--------------------
// All Orders (SIGNED)
/*
GET /api/v3/allOrders

Name		Type	Mandatory	Description
symbol		STRING	YES
orderId		LONG	NO
limit		INT		NO		Default 500; max 500.
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaCPP::get_allOrders(
	const char *symbol,
	long orderId,
	int limit,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_allOrders>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_allOrders> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/allOrders?";

	string querystring("symbol=");
	querystring.append(symbol);

	if (orderId > 0)
	{
		querystring.append("&orderId=");
		querystring.append(to_string(orderId));
	}

	if (limit > 0)
	{
		querystring.append("&limit=");
		querystring.append(to_string(limit));
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

	BinaCPP_logger::write_log("<BinaCPP::get_allOrders> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_allOrders> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_allOrders> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_allOrders> Failed to get anything.");
	}
}

//------------
/*
send order (SIGNED)
POST /api/v3/order

Name				Type		Mandatory	Description
symbol				STRING		YES
side				ENUM		YES
type				ENUM		YES
timeInForce			ENUM		YES
quantity			DECIMAL		YES
price				DECIMAL		YES
newClientOrderId	STRING		NO		A unique id for the order. Automatically generated by default.
stopPrice			DECIMAL		NO		Used with STOP orders
icebergQty			DECIMAL		NO		Used with icebergOrders
recvWindow			LONG		NO
timestamp			LONG		YES
*/

void BinaCPP::send_order(
	const char *symbol,
	const char *side,
	const char *type,
	const char *timeInForce,
	double quantity,
	double price,
	const char *newClientOrderId,
	double stopPrice,
	double icebergQty,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::send_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::send_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/order?";

	string action = "POST";

	string post_data("symbol=");
	post_data.append(symbol);

	post_data.append("&side=");
	post_data.append(side);

	post_data.append("&type=");
	post_data.append(type);
	if (strcmp(type, "MARKET")) // type != MARKET
	{
		post_data.append("&timeInForce=");
		post_data.append(timeInForce);
		post_data.append("&price=");
		post_data.append(to_string(price));
	}
	post_data.append("&quantity=");
	post_data.append(to_string(quantity));

	if (strlen(newClientOrderId) > 0)
	{
		post_data.append("&newClientOrderId=");
		post_data.append(newClientOrderId);
	}

	if (stopPrice > 0.0)
	{
		post_data.append("&stopPrice=");
		post_data.append(to_string(stopPrice));
	}

	if (icebergQty > 0.0)
	{
		post_data.append("&icebergQty=");
		post_data.append(to_string(icebergQty));
	}

	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=");
		post_data.append(to_string(recvWindow));
	}

	post_data.append("&timestamp=");
	post_data.append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=");
	post_data.append(signature);

	BinaCPP_logger::write_log("<BinaCPP::send_order> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::send_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::send_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::send_order> Failed to get anything.");
	}
}

//------------------
/*
// get order (SIGNED)
GET /api/v3/order

Name				Type	Mandatory	Description
symbol				STRING	YES
orderId				LONG	NO
origClientOrderId		STRING	NO
recvWindow			LONG	NO
timestamp			LONG	YES
*/

void BinaCPP::get_order(
	const char *symbol,
	long orderId,
	const char *origClientOrderId,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/order?";
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

	BinaCPP_logger::write_log("<BinaCPP::get_order> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_order> Failed to get anything.");
	}

	BinaCPP_logger::write_log("<BinaCPP::get_order> Done.\n");
}

//------------
/*
DELETE /api/v3/order
cancel order (SIGNED)

symbol				STRING	YES
orderId				LONG	NO
origClientOrderId		STRING	NO
newClientOrderId		STRING	NO	Used to uniquely identify this cancel. Automatically generated by default.
recvWindow			LONG	NO
timestamp			LONG	YES

*/

void BinaCPP::cancel_order(
	const char *symbol,
	long orderId,
	const char *origClientOrderId,
	const char *newClientOrderId,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::send_order>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::send_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v3/order?";

	string post_data("symbol=");
	post_data.append(symbol);

	if (orderId > 0)
	{
		post_data.append("&orderId=");
		post_data.append(to_string(orderId));
	}

	if (strlen(origClientOrderId) > 0)
	{
		post_data.append("&origClientOrderId=");
		post_data.append(origClientOrderId);
	}

	if (strlen(newClientOrderId) > 0)
	{
		post_data.append("&newClientOrderId=");
		post_data.append(newClientOrderId);
	}

	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=");
		post_data.append(to_string(recvWindow));
	}

	post_data.append("&timestamp=");
	post_data.append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=");
	post_data.append(signature);

	BinaCPP_logger::write_log("<BinaCPP::send_order> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::send_order> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::send_order> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::send_order> Failed to get anything.");
	}
}

//--------------------
// Start user data stream (API-KEY)

void BinaCPP::start_userDataStream(Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::start_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::start_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/userDataStream";

	BinaCPP_logger::write_log("<BinaCPP::start_userDataStream> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::start_userDataStream> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::start_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::start_userDataStream> Failed to get anything.");
	}
}

//--------------------
// Keepalive user data stream (API-KEY)
void BinaCPP::keep_userDataStream(const char *listenKey)
{
	BinaCPP_logger::write_log("<BinaCPP::keep_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::keep_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/userDataStream";

	string post_data("listenKey=");
	post_data.append(listenKey);

	BinaCPP_logger::write_log("<BinaCPP::keep_userDataStream> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Put(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::keep_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::keep_userDataStream> Failed to get anything.");
	}
}

//--------------------
// Keepalive user data stream (API-KEY)
void BinaCPP::close_userDataStream(const char *listenKey)
{
	BinaCPP_logger::write_log("<BinaCPP::close_userDataStream>");

	if (api_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::close_userDataStream> API Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/api/v1/userDataStream";

	string post_data("listenKey=");
	post_data.append(listenKey);

	BinaCPP_logger::write_log("<BinaCPP::close_userDataStream> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

	cpr::Response r = cpr::Delete(cpr::Url{url}, cpr::Body{post_data}, cpr::Header{{"X-MBX-APIKEY", api_key}});
	if (r.text.size() > 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::close_userDataStream> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::close_userDataStream> Failed to get anything.");
	}
}

//-------------
/*
Submit a withdraw request.

POST /wapi/v3/withdraw.html

Name		Type	Mandatory	Description
asset		STRING	YES
address		STRING	YES
addressTag	STRING	NO	Secondary address identifier for coins like XRP,XMR etc.
amount		DECIMAL	YES
name		STRING	NO	Description of the address
recvWindow	LONG	NO
timestamp	LONG	YES

*/
void BinaCPP::withdraw(
	const char *asset,
	const char *address,
	const char *addressTag,
	double amount,
	const char *name,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::withdraw>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::send_order> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/wapi/v3/withdraw.html";

	string post_data("asset=");
	post_data.append(asset);

	post_data.append("&address=");
	post_data.append(address);

	if (strlen(addressTag) > 0)
	{
		post_data.append("&addressTag=");
		post_data.append(addressTag);
	}

	post_data.append("&amount=");
	post_data.append(to_string(amount));

	if (strlen(name) > 0)
	{
		post_data.append("&name=");
		post_data.append(name);
	}

	if (recvWindow > 0)
	{
		post_data.append("&recvWindow=");
		post_data.append(to_string(recvWindow));
	}

	post_data.append("&timestamp=");
	post_data.append(to_string(get_current_ms_epoch()));

	string signature = hmac_sha256(secret_key.c_str(), post_data.c_str());
	post_data.append("&signature=");
	post_data.append(signature);

	BinaCPP_logger::write_log("<BinaCPP::withdraw> url = |%s|, post_data = |%s|", url.c_str(), post_data.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::withdraw> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::withdraw> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::withdraw> Failed to get anything.");
	}
}

/*
-GET /wapi/v3/depositHistory.html
Fetch deposit history.

Parameters:

Name		Type	Mandatory	Description
asset		STRING	NO
status		INT	NO	0(0:pending,1:success)
startTime	LONG	NO
endTime	LONG		NO
recvWindow	LONG	NO
timestamp	LONG	YES
*/
void BinaCPP::get_depositHistory(
	const char *asset,
	int status,
	long startTime,
	long endTime,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_depostHistory>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_depostHistory> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/wapi/v3/depositHistory.html?";

	string querystring("");

	if (strlen(asset) > 0)
	{
		querystring.append("asset=");
		querystring.append(asset);
	}

	if (status > 0)
	{
		querystring.append("&status=");
		querystring.append(to_string(status));
	}

	if (startTime > 0)
	{
		querystring.append("&startTime=");
		querystring.append(to_string(startTime));
	}

	if (endTime > 0)
	{
		querystring.append("&endTime=");
		querystring.append(to_string(endTime));
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

	BinaCPP_logger::write_log("<BinaCPP::get_depostHistory> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_depostHistory> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_depostHistory> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_depostHistory> Failed to get anything.");
	}
}

//---------

/*
-GET /wapi/v3/withdrawHistory.html
Fetch withdraw history.

Parameters:

Name		Type	Mandatory	Description
asset		STRING	NO
status		INT	NO	0(0:Email Sent,1:Cancelled 2:Awaiting Approval 3:Rejected 4:Processing 5:Failure 6Completed)
startTime	LONG	NO
endTime	LONG		NO
recvWindow	LONG	NO
timestamp	LONG	YES
*/

void BinaCPP::get_withdrawHistory(
	const char *asset,
	int status,
	long startTime,
	long endTime,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/wapi/v3/withdrawHistory.html?";

	string querystring("");

	if (strlen(asset) > 0)
	{
		querystring.append("asset=");
		querystring.append(asset);
	}

	if (status > 0)
	{
		querystring.append("&status=");
		querystring.append(to_string(status));
	}

	if (startTime > 0)
	{
		querystring.append("&startTime=");
		querystring.append(to_string(startTime));
	}

	if (endTime > 0)
	{
		querystring.append("&endTime=");
		querystring.append(to_string(endTime));
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

	BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory> url = |%s|", url.c_str());

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
			BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_withdrawHistory> Failed to get anything.");
	}
}

//--------------
/*
-GET /wapi/v3/depositAddress.html
Fetch deposit address.

Parameters:

Name		Type	Mandatory	Description
asset		STRING	YES
recvWindow	LONG	NO
timestamp	LONG	YES

*/

void BinaCPP::get_depositAddress(
	const char *asset,
	long recvWindow,
	Json::Value &json_result)
{
	BinaCPP_logger::write_log("<BinaCPP::get_depositAddress>");

	if (api_key.size() == 0 || secret_key.size() == 0)
	{
		BinaCPP_logger::write_log("<BinaCPP::get_depositAddress> API Key and Secret Key has not been set.");
		return;
	}

	string url(BINANCE_SPOT_HOST);
	url += "/wapi/v3/depositAddress.html?";

	string querystring("asset=");
	querystring.append(asset);

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

	BinaCPP_logger::write_log("<BinaCPP::get_depositAddress> url = |%s|", url.c_str());

	cpr::Response r = cpr::Put(cpr::Url{url}, cpr::Header{{"X-MBX-APIKEY", api_key}});
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
			BinaCPP_logger::write_log("<BinaCPP::get_depositAddress> Error ! %s", e.what());
		}
		BinaCPP_logger::write_log("<BinaCPP::get_depositAddress> Done.");
	}
	else
	{
		BinaCPP_logger::write_log("<BinaCPP::get_depositAddress> Failed to get anything.");
	}
}
