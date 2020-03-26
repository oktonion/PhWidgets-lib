/* Link header for application - AppBuilder 2.03  */

extern ApContext_t AbContext;

ApWindowLink_t TEST_WINDOW = {
	"TEST_WINDOW.wgtw",
	&AbContext,
	NULL, 0, 0
	};

ApDialogLink_t Dialog0 = {
	"Dialog0.wgtd",
	&AbContext,
	NULL, 13, 0
	};

ApPictureLink_t Picture0 = {
	"Picture0.wgtp",
	&AbContext,
	NULL,
	23, 0
	};

ApMenuLink_t Menu0 = {
	"Menu0",
	"",
	NULL,
	NULL,
	2,
	NULL,
	& AbContext,
	NULL,
	26, 0, 0
	};

