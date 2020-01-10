type route =
  | GamePlay
  | NotFound;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) =>
    ReasonReact.Update(
      {
        route;
      },
    )
  };

let component = ReasonReact.reducerComponent("App");

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | []
  | ["game"] => GamePlay
  | _ => NotFound
  };

let make = _children => {
  ...component,
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },

  initialState: () => {
    route: mapUrlToRoute(ReasonReactRouter.dangerouslyGetInitialUrl()),
  },

  reducer: (action, _state) =>
    switch (action) {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    },

  render: ({state: {route}}) =>
    <div>
      {switch (route) {
       | GamePlay => <Game />
       | NotFound => <PageNotFound />
       }}
    </div>,
};