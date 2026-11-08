package android

type Variant struct {
	Arch    string
	Product string
	Build   string
}

func DefaultVariant(config *Config) Variant {
	return Variant{
		Arch:    config.Arch,
		Product: config.Product,
		Build:   config.Variant,
	}
}

func (v Variant) String() string {
	return v.Product + "_" + v.Arch + "_" + v.Build
}
