import { requireNativeViewManager } from 'expo-modules-core';
import * as React from 'react';

import { ExpoPanoramaViewProps } from './ExpoPanoramaView.types';

const NativeView: React.ComponentType<ExpoPanoramaViewProps> =
  requireNativeViewManager('ExpoPanoramaView');

export default function ExpoPanoramaView(props: ExpoPanoramaViewProps) {
  return <NativeView {...props} />;
}
