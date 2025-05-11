#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/XAsyncBlock.hpp"
#include "engine/uwp/XStoreAddonLicense.hpp"
#include "engine/uwp/XStoreCanAcquireLicenseResult.hpp"
#include "engine/uwp/XStoreConsumableResult.hpp"
#include "engine/uwp/XStoreGameLicense.hpp"
#include "engine/uwp/XStorePackageUpdate.hpp"
#include "engine/uwp/XStoreProduct.hpp"
#include "engine/uwp/XStoreRateAndReviewResult.hpp"
#include "engine/uwp/XTaskQueueRegistrationToken.hpp"
#include "engine/uwp/enums/XUserAddOptions.hpp"

namespace uwp {
	class IStoreImpl1 : public IUnknown {
	public:
		virtual HRESULT XStoreCreateContext(const XUserHandle user, XStoreContextHandle* store_context_handle) = 0;
		virtual void XStoreCloseContextHandle(XStoreContextHandle store_context_handle) = 0;
		virtual HRESULT XStoreQueryAssociatedProductsAsync(const XStoreContextHandle store_context_handle, XStoreProductKind product_kinds,
			std::uint32_t max_items_to_retrieve_per_page, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryAssociatedProductsResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreQueryProductsAsync(const XStoreContextHandle store_context_handle, XStoreProductKind product_kinds, const char** store_ids,
			std::size_t store_ids_count, const char** action_filters, std::size_t action_filters_count, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryProductsResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreQueryEntitledProductsAsync(const XStoreContextHandle store_context_handle, XStoreProductKind product_kinds,
			std::uint32_t max_items_to_retrieve_per_page, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryEntitledProductsResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreQueryProductForCurrentGameAsync(const XStoreContextHandle store_context_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryProductForCurrentGameResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreQueryProductForPackageAsync(const XStoreContextHandle store_context_handle, XStoreProductKind product_kinds,
			const char* package_identifier, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryProductForPackageResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreEnumerateProductsQuery(const XStoreProductQueryHandle product_query_handle, void* context,
			XStoreProductQueryCallback* callback) = 0;
		virtual bool XStoreProductsQueryHasMorePages(const XStoreProductQueryHandle product_query_handle) = 0;
		virtual HRESULT XStoreProductsQueryNextPageAsync(const XStoreProductQueryHandle product_query_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreProductsQueryNextPageResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual void XStoreCloseProductsQueryHandle(XStoreProductQueryHandle product_query_handle) = 0;
		virtual HRESULT XStoreAcquireLicenseForPackageAsync(const XStoreContextHandle store_context_handle, const char* package_identifier,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreAcquireLicenseForPackageResult(XAsyncBlock* async, XStoreLicenseHandle* store_license_handle) = 0;
		virtual bool XStoreIsLicenseValid(const XStoreLicenseHandle store_license_handle) = 0;
		virtual void XStoreCloseLicenseHandle(XStoreLicenseHandle store_license_handle) = 0;
		virtual HRESULT XStoreCanAcquireLicenseForStoreIdAsync(const XStoreContextHandle store_context_handle, const char* store_product_id,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreCanAcquireLicenseForStoreIdResult(XAsyncBlock* async, XStoreCanAcquireLicenseResult* store_can_acquire_license) = 0;
		virtual HRESULT XStoreCanAcquireLicenseForPackageAsync(const XStoreContextHandle store_context_handle, const char* package_identifier,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreCanAcquireLicenseForPackageResult(XAsyncBlock* async, XStoreCanAcquireLicenseResult* store_can_acquire_license) = 0;
		virtual HRESULT XStoreQueryGameLicenseAsync(const XStoreContextHandle store_context_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryGameLicenseResult(XAsyncBlock* async, XStoreGameLicense* license) = 0;
		virtual HRESULT XStoreQueryAddOnLicensesAsync(const XStoreContextHandle store_context_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryAddOnLicensesResultCount(XAsyncBlock* async, std::uint32_t* count) = 0;
		virtual HRESULT XStoreQueryAddOnLicensesResult(XAsyncBlock* async, std::uint32_t count, XStoreAddonLicense* addon_licenses) = 0;
		virtual HRESULT XStoreQueryConsumableBalanceRemainingAsync(const XStoreContextHandle store_context_handle, const char* store_product_id,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryConsumableBalanceRemainingResult(XAsyncBlock* async, XStoreConsumableResult* consumable_result) = 0;
		virtual HRESULT XStoreReportConsumableFulfillmentAsync(const XStoreContextHandle store_context_handle, const char* store_product_id,
			std::uint32_t quantity, GUID tracking_id, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreReportConsumableFulfillmentResult(XAsyncBlock* async, XStoreConsumableResult* consumable_result) = 0;
		virtual HRESULT XStoreGetUserCollectionsIdAsync(const XStoreContextHandle store_context_handle, const char* service_ticket, const char* publisher_user_id,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreGetUserCollectionsIdResultSize(XAsyncBlock* async, std::size_t* size) = 0;
		virtual HRESULT XStoreGetUserCollectionsIdResult(XAsyncBlock* async, std::size_t size, char* result) = 0;
		virtual HRESULT XStoreGetUserPurchaseIdAsync(const XStoreContextHandle store_context_handle, const char* service_ticket, const char* publisher_user_id,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreGetUserPurchaseIdResultSize(XAsyncBlock* async, std::size_t* size) = 0;
		virtual HRESULT XStoreGetUserPurchaseIdResult(XAsyncBlock* async, std::size_t size, char* result) = 0;
		virtual HRESULT XStoreQueryLicenseTokenAsync(const XStoreContextHandle store_context_handle, const char** product_ids, std::size_t product_ids_count,
			const char* custom_developer_string, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryLicenseTokenResultSize(XAsyncBlock* async, std::size_t* size) = 0;
		virtual HRESULT XStoreQueryLicenseTokenResult(XAsyncBlock* async, std::size_t size, char* result) = 0;
		virtual HRESULT XStoreSendRequestAsync(const XStoreContextHandle store_context_handle, std::uint32_t request_kind, const char* parameters_as_json,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreSendRequestResultSize(XAsyncBlock* async, std::size_t* size) = 0;
		virtual HRESULT XStoreSendRequestResult(XAsyncBlock* async, std::size_t size, char* result) = 0;
		virtual HRESULT XStoreShowPurchaseUIAsync(const XStoreContextHandle store_context_handle, const char* store_id, const char* name,
			const char* extended_json_data, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowPurchaseUIResult(XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowRateAndReviewUIAsync(const XStoreContextHandle store_context_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowRateAndReviewUIResult(XAsyncBlock* async, XStoreRateAndReviewResult* result) = 0;
		virtual HRESULT XStoreShowRedeemTokenUIAsync(const XStoreContextHandle store_context_handle, const char* token, const char** allowed_store_ids,
			std::size_t allowed_store_ids_count, bool disallow_csv_redemption, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowRedeemTokenUIResult(XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryGameAndDlcPackageUpdatesAsync(const XStoreContextHandle store_context_handle, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryGameAndDlcPackageUpdatesResultCount(XAsyncBlock* async, std::uint32_t* count) = 0;
		virtual HRESULT XStoreQueryGameAndDlcPackageUpdatesResult(XAsyncBlock* async, std::uint32_t count, XStorePackageUpdate* package_updates) = 0;
		virtual HRESULT XStoreDownloadPackageUpdatesAsync(const XStoreContextHandle store_context_handle, const char** package_identifiers,
			std::size_t package_identifiers_count, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreDownloadPackageUpdatesResult(XAsyncBlock* async) = 0;
		virtual HRESULT XStoreDownloadAndInstallPackageUpdatesAsync(const XStoreContextHandle store_context_handle, const char** package_identifiers,
			std::size_t package_identifiers_count, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreDownloadAndInstallPackageUpdatesResult(XAsyncBlock* async) = 0;
		virtual HRESULT XStoreDownloadAndInstallPackagesAsync(const XStoreContextHandle store_context_handle, const char** store_ids, std::size_t store_ids_count,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreDownloadAndInstallPackagesResultCount(XAsyncBlock* async, std::uint32_t* count) = 0;
		virtual HRESULT XStoreDownloadAndInstallPackagesResult(XAsyncBlock* async, std::uint32_t count, char(*package_identifiers)[0x20 + 1]) = 0;
		virtual HRESULT XStoreQueryPackageIdentifier(const char* store_id, std::size_t size, char* package_identifier) = 0;
		virtual HRESULT XStoreRegisterGameLicenseChanged(XStoreContextHandle store_context_handle, XTaskQueueHandle queue, void* context,
			XStoreGameLicenseChangedCallback* callback, XTaskQueueRegistrationToken* token) = 0;
		virtual bool XStoreUnregisterGameLicenseChanged(XStoreContextHandle store_context_handle, XTaskQueueRegistrationToken token, bool wait) = 0;
		virtual HRESULT XStoreRegisterPackageLicenseLost(XStoreLicenseHandle license_handle, XTaskQueueHandle queue, void* context,
			XStorePackageLicenseLostCallback* callback, XTaskQueueRegistrationToken* token) = 0;
		virtual bool XStoreUnregisterPackageLicenseLost(XStoreLicenseHandle license_handle, XTaskQueueRegistrationToken token, bool wait) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl1, 0x0008);
}
