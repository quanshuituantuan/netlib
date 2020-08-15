Name:           programme
Version:        0.0.0
Release:        1%{?dist}
Summary:        programme
Group:          programme

License:        programme
URL:            programme

AutoReqProv:    no

%description
%{name} provide programme

%prep

%build

%install
make -C %{buildroot}/.. install DESTDIR="%{buildroot}"

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_bindir}/programme
