#include <cJSON.h>
#include <netease_api.h>
#include <request.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int captcha_sent(const char *cookieJar, const char *cellphone, const char *ctcode, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();

	cJSON_AddStringToObject(jsonObject, "ctcode", ctcode);
	cJSON_AddStringToObject(jsonObject, "cellphone", cellphone);
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/sms/captcha/sent", 0, response, NCM_WEAPI);

	cJSON_Delete(jsonObject);
	return code;
}
/*
 * return -1 when uid too long
 */
int captcha_verify(const char *cookieJar, const char *cellphone, const char *ctcode, const char *captcha, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();

	cJSON_AddStringToObject(jsonObject, "ctcode", ctcode);
	cJSON_AddStringToObject(jsonObject, "cellphone", cellphone);
	cJSON_AddStringToObject(jsonObject, "captcha", captcha);
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/sms/captcha/verify", 0, response, NCM_WEAPI);

	cJSON_Delete(jsonObject);
	return code;
}
int user_followeds(const char *cookieJar, const char *uid, int offset, int limit, const char *order, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	char realURL[128];
	memset(realURL, 0, 128);
	strcat_s(realURL, 128, "https://music.163.com/eapi/user/getfolloweds/");
	if (strlen(uid) > 127 - 45) {
		printf("[user_followeds]uid too long");
		return -1;
	}
	strcat_s(realURL, 128, uid);

	cJSON_AddStringToObject(jsonObject, "userId", uid);
	cJSON_AddStringToObject(jsonObject, "time", "0");
	cJSON_AddNumberToObject(jsonObject, "limit", limit);
	cJSON_AddNumberToObject(jsonObject, "offset", offset);

	cJSON_AddStringToObject(jsonObject, "getcounts", "true");
	// cJSON_AddBoolToObject(jsonObject, "getcounts", 1);

	int code = NCM_request(cookieJar, jsonObject, 0, realURL, "/api/user/getfolloweds", response, NCM_EAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int user_follows(const char *cookieJar, const char *uid, const char *offset, const char *limit, const char *order,
				 char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	char realURL[128];
	memset(realURL, 0, 128);
	strcat_s(realURL, 128, "https://music.163.com/weapi/user/getfollows/");
	if (strlen(uid) > 127 - 44) {
		printf("[user_follows]uid too long");
		return -1;
	}
	strcat_s(realURL, 128, uid);

	cJSON_AddStringToObject(jsonObject, "offset", offset);
	cJSON_AddStringToObject(jsonObject, "limit", limit);
	cJSON_AddStringToObject(jsonObject, "order", order);
	int code = NCM_request(cookieJar, jsonObject, 0, realURL, 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}

int homepage_block_page(const char *cookieJar, int isRefresh, const char *cursor, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	cJSON *customCookie = cJSON_CreateObject();
	cJSON_AddStringToObject(customCookie, "os", "ios");
	cJSON_AddStringToObject(customCookie, "appver", "8.7.01");

	cJSON_AddBoolToObject(jsonObject, "refresh", isRefresh);
	if (cursor) {
		cJSON_AddStringToObject(jsonObject, "cursor", cursor);
	}
	int code = NCM_request(cookieJar, jsonObject, customCookie, "https://music.163.com/weapi/homepage/block/page", 0, response,
						   NCM_WEAPI);
	cJSON_Delete(jsonObject);
	cJSON_Delete(customCookie);
	return code;
}
int login_qr_key(const char *cookieJar, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();

	cJSON_AddNumberToObject(jsonObject, "type", 1);
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/login/qrcode/unikey", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int login_qr_check(const char *cookieJar, const char *key, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();

	cJSON_AddNumberToObject(jsonObject, "type", 1);
	cJSON_AddStringToObject(jsonObject, "key", key);
	int code =
		NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/login/qrcode/client/login", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int logout(const char *cookieJar, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/logout", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int login_refresh(const char *cookieJar, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/login/token/refresh", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int personalized(const char *cookieJar, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();

	cJSON_AddNumberToObject(jsonObject, "limit", 30);
	cJSON_AddNumberToObject(jsonObject, "n", 1000);
	cJSON_AddBoolToObject(jsonObject, "total", 1);
	int code = NCM_request(cookieJar, jsonObject, 0, "https://music.163.com/weapi/personalized/playlist", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	return code;
}
int personalized_newsong(const char *cookieJar, char **response) {
	cJSON *customCookie = cJSON_CreateObject();
	cJSON_AddStringToObject(customCookie, "os", "pc");

	cJSON *jsonObject = cJSON_CreateObject();
	cJSON_AddNumberToObject(jsonObject, "areaId", 0);
	cJSON_AddNumberToObject(jsonObject, "limit", 10);
	cJSON_AddStringToObject(jsonObject, "type", "recommend");
	int code = NCM_request(cookieJar, jsonObject, customCookie, "https://music.163.com/weapi/personalized/playlist", 0, response,
						   NCM_WEAPI);
	cJSON_Delete(jsonObject);
	cJSON_Delete(customCookie);
	return code;
}
int like(const char *cookieJar, const char *trackId, int isLiked, char **response) {
	cJSON *customCookie = cJSON_CreateObject();
	cJSON_AddStringToObject(customCookie, "os", "pc");

	cJSON_AddStringToObject(customCookie, "appver", "2.9.7");

	cJSON *jsonObject = cJSON_CreateObject();
	cJSON_AddStringToObject(jsonObject, "alg", "itembased");
	cJSON_AddStringToObject(jsonObject, "trackId", trackId);
	cJSON_AddBoolToObject(jsonObject, "like", isLiked);
	cJSON_AddStringToObject(jsonObject, "time", "3");

	int code = NCM_request(cookieJar, jsonObject, customCookie, "https://music.163.com/weapi/radio/like", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	cJSON_Delete(customCookie);
	return code;
}
int playlist_create(const char *cookieJar, const char *name, int isPrivacy, PLAYLIST_TYPE playlistType, char **response) {
	cJSON *jsonObject = cJSON_CreateObject();
	cJSON *customCookie = cJSON_CreateObject();
	cJSON_AddStringToObject(customCookie, "os", "pc");
	cJSON_AddStringToObject(jsonObject, "name", name);
	if (isPrivacy) {
		cJSON_AddStringToObject(jsonObject, "privacy", "10");
	} else {
		cJSON_AddStringToObject(jsonObject, "privacy", "0");
	}
	switch (playlistType) {
	case NCM_PLAYLIST_NORMAL:
		cJSON_AddStringToObject(jsonObject, "type", "NORMAL");
		break;
	case NCM_PLAYLIST_VIDEO:
		cJSON_AddStringToObject(jsonObject, "type", "VIDEO");
		break;
	case NCM_PLAYLIST_SHARED:
		cJSON_AddStringToObject(jsonObject, "type", "SHARED");
		break;
	}
	// here we replace api with weapi directly in the function body
	// that is, https://music.163.com/api/radio/like to https://music.163.com/weapi/radio/like
	int code =
		NCM_request(cookieJar, jsonObject, customCookie, "https://music.163.com/weapi/playlist/create", 0, response, NCM_WEAPI);
	cJSON_Delete(jsonObject);
	cJSON_Delete(customCookie);
	return code;
}